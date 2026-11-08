#include "../headers/includes.h"
#include "../../imgui/imgui_freetype.h"
#include "../../imgui/backends/imgui_impl_dx11.h"
#include <algorithm>

static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

void c_font::update()
{
    if (var->gui.dpi_changed)
    {
        var->gui.dpi = var->gui.stored_dpi / 100.f;

        ImFontConfig cfg;
        cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_Bitmap;
        cfg.FontDataOwnedByAtlas = false;

        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->Clear();

        // Inter must be built before Font Awesome so Fonts[0] / default text is never icon-only.
        std::stable_sort(data.begin(), data.end(), [](const font_data& a, const font_data& b) {
            const bool a_inter = (a.data == inter_medium_data);
            const bool b_inter = (b.data == inter_medium_data);
            return a_inter && !b_inter;
        });

        for (auto& font_t : data)
        {
            ImFontConfig font_cfg = cfg;
            const ImWchar* ranges = font_t.glyph_ranges ? font_t.glyph_ranges : io.Fonts->GetGlyphRangesCyrillic();

            // Load each font separately as requested.
            font_t.font = io.Fonts->AddFontFromMemoryTTF(font_t.data.data(), (int)font_t.data.size(), SCALE(font_t.size), &font_cfg, ranges);
        }

        io.Fonts->Build();

        ImFont* default_text = nullptr;
        for (auto& font_t : data)
        {
            if (font_t.data == inter_medium_data && font_t.size == 14.f)
            {
                default_text = font_t.font;
                break;
            }
        }
        if (!default_text)
        {
            for (auto& font_t : data)
            {
                if (font_t.data == inter_medium_data)
                {
                    default_text = font_t.font;
                    break;
                }
            }
        }
        io.FontDefault = default_text;

        ImGui_ImplDX11_CreateDeviceObjects();

        var->gui.dpi_changed = false;
    }
}

ImFont* c_font::get(std::vector<unsigned char> font_data, float size, const ImWchar* glyph_ranges)
{
    for (auto& font : data)
    {
        if (font.data == font_data && font.size == size)
        {
            return font.font;
        }
    }

    if (font_data == icon_data)
        glyph_ranges = icon_ranges;

    add(font_data, size, glyph_ranges);

    var->gui.dpi_changed = true;

    return get(font_data, size, glyph_ranges);
}

void c_font::add(std::vector<unsigned char> font_data, float size, const ImWchar* glyph_ranges)
{
    data.push_back({ font_data, size, nullptr, glyph_ranges });
}