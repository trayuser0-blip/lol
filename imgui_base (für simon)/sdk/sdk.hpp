#pragma once

#include <cstdint>
#include <cwchar>
#include <string>
#include <vector>
#include <cfloat>

    // Basic UI-compatible math and color types.
    // Keep these names and member names compatible with the supplied UI source.


struct fvector
{
    double x, y, z;

    constexpr fvector() noexcept : x(0), y(0), z(0) {}
    constexpr fvector(double X, double Y, double Z) noexcept
        : x(X), y(Y), z(Z) {
    }

    constexpr bool operator==(const fvector& v) const noexcept
    {
        return x == v.x && y == v.y && z == v.z;
    }

    constexpr fvector operator+(const fvector& v) const noexcept
    {
        return { x + v.x, y + v.y, z + v.z };
    }

    constexpr fvector operator-(const fvector& v) const noexcept
    {
        return { x - v.x, y - v.y, z - v.z };
    }

    constexpr fvector operator*(double value) const noexcept
    {
        return { x * value, y * value, z * value };
    }
};

struct fvector2d
{
    double x, y;

    constexpr fvector2d() noexcept : x(0), y(0) {}
    constexpr fvector2d(double X, double Y) noexcept : x(X), y(Y) {}
};

struct frotator
{
    double pitch, yaw, roll;

    constexpr frotator() noexcept : pitch(0), yaw(0), roll(0) {}
    constexpr frotator(double P, double Y, double R) noexcept
        : pitch(P), yaw(Y), roll(R) {
    }
};

struct fmatrix
{
    double m[4][4]{};
};

struct fname
{
    std::uint32_t index = 0;
    std::int32_t number = 0;

    constexpr fname() noexcept = default;
    constexpr fname(std::uint32_t Index, std::int32_t Number = 0) noexcept
        : index(Index), number(Number) {
    }
};

template <typename T>
struct tarray
{
    T* data = nullptr;
    std::int32_t count = 0;
    std::int32_t max = 0;

    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const { return data[index]; }

    int size() const noexcept { return count; }
    bool valid(int index) const noexcept
    {
        return data != nullptr && index >= 0 && index < count;
    }
};

struct fstring : public tarray<wchar_t>
{
    fstring() = default;

    explicit fstring(const wchar_t* value)
    {
        if (value && *value)
        {
            data = const_cast<wchar_t*>(value);
            count = static_cast<std::int32_t>(std::wcslen(value) + 1);
            max = count;
        }
    }

    wchar_t* c_str() noexcept { return data; }
    const wchar_t* c_str() const noexcept { return data; }
    bool valid() const noexcept { return data != nullptr; }
};

struct ftextdata
{
    char pad_0[0x20]{};
    fstring name;
};

struct ftext
{
    ftextdata* data = nullptr;

    wchar_t* c_str() const noexcept
    {
        return data && data->name.valid() ? data->name.c_str() : nullptr;
    }
};

// End of menu-only compatibility types.
//
// Removed intentionally:
// - offsets and game-version-specific addresses
// - uobject::process_event / static_find_object
// - actor, pawn, player-controller, weapon, mesh, world and engine access
// - game memory access and game-state functionality
//
// If another menu source file reports an unknown SDK type, do not restore
// game-memory functionality just to silence the error. Identify the exact
// UI dependency and add only a harmless data-type declaration if appropriate.
