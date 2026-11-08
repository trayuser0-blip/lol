// Eigenständiger ImGui-Teststarter:
// Beim Start erscheint die Konsole. Erst Eingabe von "1" + Enter öffnet ImGui.
// Benötigt: Dear ImGui + Win32/DX11-Backend-Dateien und d3d11.lib.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11.h>
#include <iostream>

#include "imgui simon/imgui/imgui.h"
#include "imgui simon/imgui/backends/imgui_impl_win32.h"
#include "imgui simon/imgui/backends/imgui_impl_dx11.h"

#pragma comment(lib, "d3d11.lib")

static ID3D11Device* g_device = nullptr;
static ID3D11DeviceContext* g_context = nullptr;
static IDXGISwapChain* g_swapChain = nullptr;
static ID3D11RenderTargetView* g_renderTarget = nullptr;
static bool g_running = true;

static void CreateRenderTarget()
{
    ID3D11Texture2D* backBuffer = nullptr;
    if (SUCCEEDED(g_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))))
    {
        g_device->CreateRenderTargetView(backBuffer, nullptr, &g_renderTarget);
        backBuffer->Release();
    }
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
    if (g_swapChain) { g_swapChain->Release(); g_swapChain = nullptr; }
    if (g_context) { g_context->Release(); g_context = nullptr; }
    if (g_device) { g_device->Release(); g_device = nullptr; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return TRUE;

    switch (msg)
    {
    case WM_SIZE:
        if (g_device && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_swapChain->ResizeBuffers(0, (UINT)LOWORD(lParam),
                (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
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

// Beispiel-Menü: Hier kannst du später deine eigenen ImGui-Elemente ergänzen.
static void RenderImGui()
{
    static bool exampleCheck = true;
    static bool anotherCheck = false;
    static float exampleValue = 50.0f;
    static int selectedTab = 0;

    ImGui::SetNextWindowSize(ImVec2(560, 390), ImGuiCond_FirstUseEver);
    ImGui::Begin("ImGui Test Menu", nullptr, ImGuiWindowFlags_NoCollapse);

    ImGui::TextUnformatted("ImGui wurde erfolgreich geladen.");
    ImGui::Separator();

    if (ImGui::Button("Main", ImVec2(100, 28))) selectedTab = 0;
    ImGui::SameLine();
    if (ImGui::Button("Visuals", ImVec2(100, 28))) selectedTab = 1;
    ImGui::SameLine();
    if (ImGui::Button("Settings", ImVec2(100, 28))) selectedTab = 2;

    ImGui::Spacing();
    ImGui::Separator();

    if (selectedTab == 0)
    {
        ImGui::TextUnformatted("Main");
        ImGui::Checkbox("Example checkbox", &exampleCheck);
        ImGui::Checkbox("Another option", &anotherCheck);
        ImGui::SliderFloat("Example slider", &exampleValue, 0.0f, 100.0f, "%.0f");
    }
    else if (selectedTab == 1)
    {
        ImGui::TextUnformatted("Visual test");
        ImGui::Text("This is a sample ImGui panel.");
        ImGui::ColorEdit3("Preview color", (float*)&ImGui::GetStyle().Colors[ImGuiCol_CheckMark]);
    }
    else
    {
        ImGui::TextUnformatted("Settings");
        ImGui::Text("Close the window with the X button or Alt+F4.");
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextDisabled("Standalone ImGui / DirectX 11 test");
    ImGui::End();
}

int main()
{
    std::cout << R"(
 _____ _                 _   _         _____ _                _
/ ____| |               | | (_)       / ____| |              | |
| |    | |__   __ _  ___ | |_ _  ___  | |    | |__   ___  __ _| |_ ___
| |____| | | | (_| | (_) | |_| | (__  | |____| | | |  __/ (_| | |_\__ \
 \_____|_| |_|\__,_|\___/ \__|_|\___|  \_____|_| |_|\___|\__,_|\__|___/
)" << "\n\n";
    std::cout << "[1] Load ImGui\n";
    std::cout << "[0] Exit\n\n";
    std::cout << "Auswahl: ";

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

    HWND hwnd = CreateWindowW(className, L"ImGui Test Menu",
        WS_OVERLAPPEDWINDOW, 100, 100, 800, 600,
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
        D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0
    };
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_10_0;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        levels, ARRAYSIZE(levels), D3D11_SDK_VERSION, &sd,
        &g_swapChain, &g_device, &featureLevel, &g_context);

    if (FAILED(hr))
    {
        CleanupD3D();
        DestroyWindow(hwnd);
        UnregisterClassW(className, wc.hInstance);
        MessageBoxW(nullptr, L"DirectX 11 konnte nicht initialisiert werden.",
            L"Fehler", MB_ICONERROR);
        return 1;
    }

    CreateRenderTarget();
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    if (!ImGui_ImplWin32_Init(hwnd) ||
        !ImGui_ImplDX11_Init(g_device, g_context))
    {
        ImGui::DestroyContext();
        CleanupD3D();
        DestroyWindow(hwnd);
        UnregisterClassW(className, wc.hInstance);
        return 1;
    }

    while (g_running)
    {
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        if (!g_running)
            break;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        RenderImGui();

        ImGui::Render();
        const float clearColor[4] = { 0.08f, 0.08f, 0.10f, 1.0f };
        g_context->OMSetRenderTargets(1, &g_renderTarget, nullptr);
        g_context->ClearRenderTargetView(g_renderTarget, clearColor);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_swapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanupD3D();
    DestroyWindow(hwnd);
    UnregisterClassW(className, wc.hInstance);
    return 0;
}
