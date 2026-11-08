#pragma once
#include <Windows.h>


inline bool is_bad_write_ptr(LPVOID ptr, UINT_PTR size)
{
    return ptr ? false : true;
}

inline bool valid_pointer(uintptr_t address)
{
	return (address > 0x10000 && address < 0x00007FFFFFFEFFFFULL);
}

template<typename ReadT>
ReadT read(DWORD_PTR address, const ReadT& def = ReadT())
{
    if (valid_pointer(address)) {
        __try {
            return *(ReadT*)(address);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }
    return def;
}

template<typename WriteT>
void write(DWORD_PTR address, WriteT value)
{
    if (valid_pointer(address)) {
        __try {
            *(WriteT*)(address) = value;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }
}

#include <vector>
#include <string>
#include <Psapi.h>

inline uintptr_t FindPattern(const char* signature)
{
    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + strlen(pattern);

        for (auto current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    auto dosHeader = (PIMAGE_DOS_HEADER)GetModuleHandleA(NULL);
    auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)dosHeader + dosHeader->e_lfanew);
    auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto scanBytes = reinterpret_cast<std::uint8_t*>(dosHeader);

    auto patternBytes = pattern_to_byte(signature);
    auto s = patternBytes.size();
    auto d = patternBytes.data();

    for (auto i = 0ul; i < sizeOfImage - s; ++i) {
        bool found = true;
        for (auto j = 0ul; j < s; ++j) {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            return reinterpret_cast<uintptr_t>(&scanBytes[i]);
        }
    }
    return 0;
}
