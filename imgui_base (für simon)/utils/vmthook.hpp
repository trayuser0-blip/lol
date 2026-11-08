#pragma once

#define MEM_COMMIT 0x1000
#define MEM_RESERVE 0x2000
#define PAGE_READWRITE 0x04
#define PAGE_EXECUTE_READ 0x20

#include <Windows.h>


template <typename hook_type>
__declspec(noinline) hook_type vmt(void* address, void* hook_function, int index) {
    if (!address || !hook_function) return nullptr;

    unsigned __int64** instance = reinterpret_cast<unsigned __int64**>(address);
    unsigned __int64* original_vtable = *instance;
    if (!original_vtable) return nullptr;

    int tableSize = 512;
    unsigned __int64* shadow_vtable = reinterpret_cast<unsigned __int64*>(
    VirtualAlloc(nullptr, tableSize * sizeof(unsigned __int64), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)
    );
    if (!shadow_vtable) return nullptr;

    for (int i = 0; i < tableSize; i++)
    shadow_vtable[i] = original_vtable[i];

    void* original_fn = reinterpret_cast<void*>(original_vtable[index]);
    shadow_vtable[index] = reinterpret_cast<unsigned __int64>(hook_function);

    unsigned long oldProtect;
    VirtualProtect(shadow_vtable, tableSize * sizeof(unsigned __int64), PAGE_EXECUTE_READ, &oldProtect);

    *instance = shadow_vtable;

    return reinterpret_cast<hook_type>(original_fn);
}