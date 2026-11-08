#pragma once

struct flinearcolor
{
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float a = 1.0f;

    flinearcolor() = default;

    flinearcolor(float red, float green, float blue, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha)
    {
    }
};