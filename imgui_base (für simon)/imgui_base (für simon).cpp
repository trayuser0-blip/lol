
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <iostream>
#include <cstdio>

#include "../headers/includes.h"
#include "imgui simon/imgui/backends/imgui_impl_win32.h"
#include "imgui simon/imgui/backends/imgui_impl_dx11.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

static ID3D11Device* g_device = nullptr;
static ID3D11DeviceContext* g_context = nullptr;
static IDXGISwapChain* g_swapChain = nullptr;
static ID3D11RenderTargetView* g_renderTarget = nullptr;

static bool g_running = true;
static bool g_win32Initialized = false;
static bool g_dx11Initialized = false;
static bool g_imguiContextCreated = false;
static bool g_resizePending = false;

static UINT g_resizeWidth = 0;
static UINT g_resizeHeight = 0;

static bool CreateRenderTarget()
{
    if (!g_swapChain || !g_device)
        return false;

    ID3D11Texture2D* backBuffer = nullptr;

    HRESULT hr = g_swapChain->GetBuffer(
        0, IID_PPV_ARGS(&backBuffer));

    if (FAILED(hr))
        return false;

    hr = g_device->CreateRenderTargetView(
        backBuffer, nullptr, &g_renderTarget);

    backBuffer->Release();
    return SUCCEEDED(hr);
}

static void CleanupRenderTarget()
{
    if (g_renderTarget)
    {
        g_renderTarget->Release();
        g_renderTarget = nullptr;
    }
}

static void CleanupD3D()
{
    CleanupRenderTarget();

    if (g_swapChain)
    {
        g_swapChain->Release();
        g_swapChain = nullptr;
    }

    if (g_context)
    {
        g_context->ClearState();
        g_context->Flush();
        g_context->Release();
        g_context = nullptr;
    }

    if (g_device)
    {
        g_device->Release();
        g_device = nullptr;
    }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

static LRESULT WINAPI WndProc(
    HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (g_win32Initialized)
    {
        if (ImGui_ImplWin32_WndProcHandler(
            hwnd, msg, wParam, lParam))
            return TRUE;
    }

    switch (msg)
    {
    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED && g_swapChain)
        {
            g_resizeWidth = LOWORD(lParam);
            g_resizeHeight = HIWORD(lParam);

            if (g_resizeWidth > 0 && g_resizeHeight > 0)
                g_resizePending = true;
        }
        return 0;

    case WM_SYSCOMMAND:
        if ((wParam & 0xFFF0) == SC_KEYMENU)
            return 0;
        break;

    case WM_DESTROY:
        g_running = false;
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static bool HandleResize()
{
    if (!g_resizePending)
        return true;

    g_resizePending = false;

    if (!g_swapChain)
        return false;

    CleanupRenderTarget();

    HRESULT hr = g_swapChain->ResizeBuffers(
        0, g_resizeWidth, g_resizeHeight,
        DXGI_FORMAT_UNKNOWN, 0);

    if (FAILED(hr))
    {
        std::cout << "[ERROR] ResizeBuffers: 0x"
            << std::hex << hr << std::dec << "\n";
        return false;
    }

    return CreateRenderTarget();
}

int main()
{
    std::cout << "[1] Load original menu\n";
    std::cout << "[0] Exit\n\n";
    std::cout << "Choice: ";

    int choice = 0;

    if (!(std::cin >> choice) || choice != 1)
        return 0;

    const wchar_t* className = L"StandaloneImGuiWindow";

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = className;

    if (!RegisterClassExW(&wc))
        return 1;

    HWND hwnd = CreateWindowW(
        className,
        L"Original ImGui Menu",
        WS_OVERLAPPEDWINDOW,
        100, 100, 1000, 700,
        nullptr, nullptr, wc.hInstance, nullptr);

    if (!hwnd)
    {
        UnregisterClassW(className, wc.hInstance);
        return 1;
    }

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 2;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    const D3D_FEATURE_LEVEL levels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_0
    };

    D3D_FEATURE_LEVEL featureLevel = {};

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        levels,
        ARRAYSIZE(levels),
        D3D11_SDK_VERSION,
        &sd,
        &g_swapChain,
        &g_device,
        &featureLevel,
        &g_context);

    if (FAILED(hr))
    {
        std::cout << "[ERROR] DirectX: 0x"
            << std::hex << hr << std::dec << "\n";
        goto cleanup;
    }

    if (!CreateRenderTarget())
    {
        std::cout << "[ERROR] Render target failed\n";
        goto cleanup;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    g_imguiContextCreated = true;

    ImGui::StyleColorsDark();

    if (!ImGui_ImplWin32_Init(hwnd))
        goto cleanup;

    g_win32Initialized = true;

    if (!ImGui_ImplDX11_Init(g_device, g_context))
        goto cleanup;

    g_dx11Initialized = true;

    // Initialize custom GUI
    gui->initialize();

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    std::cout << "[DEBUG] Render loop started\n";

    std::cout << "[CHECK] GUI pointer: "
        << (gui ? "VALID" : "NULL") << std::endl;
    while (g_running)
    {
        MSG msg = {};

        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                g_running = false;
                break;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        if (!g_running)
            break;

        if (!HandleResize())
            break;

        if (!g_renderTarget)
            continue;

        // Start ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (font)
        {
            font->update();
        }

        if (gui)
        {
            gui->render();
        }

        // Render GUI exactly once per frame
        std::cout << "[DEBUG] Calling GUI render..." << std::endl;

        if (gui)
        {
            gui->render();
            std::cout << "[DEBUG] GUI render finished!" << std::endl;
        }
        else
        {
            std::cout << "[ERROR] GUI pointer is NULL!" << std::endl;
        }

        // Finalize draw data
        ImGui::Render();

        ImDrawData* drawData = ImGui::GetDrawData();

        // Clear and render
        const float clearColor[4] = {
            0.035f, 0.035f, 0.05f, 1.0f
        };

        g_context->OMSetRenderTargets(
            1, &g_renderTarget, nullptr);

        g_context->ClearRenderTargetView(
            g_renderTarget, clearColor);

        if (drawData)
        {
            ImGui_ImplDX11_RenderDrawData(drawData);
        }

        hr = g_swapChain->Present(1, 0);

        if (FAILED(hr))
        {
            std::cout << "[ERROR] Present: 0x"
                << std::hex << hr << std::dec << "\n";
            break;
        }
    }

    std::cout << "[DEBUG] Shutting down\n";

cleanup:

    if (g_dx11Initialized)
    {
        ImGui_ImplDX11_Shutdown();
        g_dx11Initialized = false;
    }

    if (g_win32Initialized)
    {
        ImGui_ImplWin32_Shutdown();
        g_win32Initialized = false;
    }

    if (g_imguiContextCreated)
    {
        ImGui::DestroyContext();
        g_imguiContextCreated = false;
    }

    CleanupD3D();

    if (IsWindow(hwnd))
        DestroyWindow(hwnd);

    UnregisterClassW(className, wc.hInstance);

    std::cout << "[DEBUG] Shutdown complete\n";
    return 0;
}
