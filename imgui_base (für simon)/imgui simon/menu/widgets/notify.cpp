#include "../headers/functions.h"
#include "../headers/widgets.h"

void c_notify::add_notify(std::string_view text, notify_type type)
{
    notifications.push_back({ notify_count++, std::string(text), type });
}

void c_notify::setup_notify()
{
    int cur_notify_value = 0;
    float accumulated_height = 0.f;

    for (auto& notification : notifications)
    {
        cur_notify_value++;
        if (notification.active_notify)
            notification.notify_timer += gui->fixed_speed(4.f);

        if (notification.notify_timer >= notify_time)
            notification.active_notify = false;

        gui->easing(notification.notify_alpha, notification.active_notify ? 1.f : 0.f, 4.f, static_easing);

        if (notification.notify_alpha > 0.f)
        {
            float target_position = accumulated_height + notify_padding.y;
            gui->easing(notification.notify_pos, target_position, 8.f, dynamic_easing);

            ImVec2 window_size = render_notify(cur_notify_value, notification.notify_alpha, notification.notify_timer, notification.notify_pos, notification.text.c_str(), notification.type);

            accumulated_height += window_size.y + notify_spacing;
        }
    }
}

ImVec2 c_notify::render_notify(int cur_notify_value, float notify_alpha, float notify_percentage, float notify_pos, const char* text, notify_type type)
{
    ImVec2 window_size;

    ImVec4 accent_border = ImVec4(0.35f, 0.95f, 1.f, 1.f);
    ImVec4 text_glow = ImVec4(0.95f, 1.f, 0.98f, 1.f);
    const char* icon = ICON_FA_CIRCLE_CHECK;

    if (type == success)
    {
        accent_border = ImVec4(0.1f, 1.f, 0.55f, 1.f);
        text_glow = ImVec4(0.2f, 1.f, 0.72f, 1.f);
        icon = ICON_FA_CIRCLE_CHECK;
    }
    else if (type == warning)
    {
        accent_border = ImVec4(1.f, 0.55f, 0.05f, 1.f);
        text_glow = ImVec4(1.f, 0.78f, 0.15f, 1.f);
        icon = ICON_FA_TRIANGLE_EXCLAMATION;
    }
    else if (type == error)
    {
        accent_border = ImVec4(1.f, 0.2f, 0.45f, 1.f);
        text_glow = ImVec4(1.f, 0.45f, 0.65f, 1.f);
        icon = ICON_FA_XMARK;
    }

    const ImU32 bg_u32 = draw->get_clr(ImVec4(0.07f, 0.07f, 0.12f, 0.94f), notify_alpha);
    const ImU32 border_u32 = draw->get_clr(accent_border, notify_alpha);

    SetNextWindowPos(ImVec2(notify_padding.x, notify_pos));
    gui->push_var(style_var_alpha, notify_alpha);
    gui->push_var(style_var_window_rounding, SCALE(14));
    gui->push_var(style_var_window_border_size, SCALE(2));
    gui->push_var(style_var_window_padding, ImVec2(SCALE(16), SCALE(12)));
    gui->push_color(style_col_window_bg, bg_u32);
    gui->push_color(style_col_border, border_u32);

    gui->begin("notify_" + std::to_string(cur_notify_value), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_Tooltip | ImGuiWindowFlags_AlwaysAutoResize);
    {
        ImDrawList* dl = gui->window_drawlist();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(SCALE(12), 0));
        ImGui::BeginGroup();

        gui->push_font(font->get(icon_data, 16));
        ImGui::PushStyleColor(ImGuiCol_Text, draw->get_clr(accent_border, 1.f));
        ImGui::TextUnformatted(icon);
        ImGui::PopStyleColor();
        gui->pop_font();

        ImGui::SameLine(0.f, 0.f);

        gui->push_font(font->get(inter_medium_data, 15));
        ImGui::PushStyleColor(ImGuiCol_Text, draw->get_clr(text_glow, 1.f));
        ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + SCALE(420));
        ImGui::TextUnformatted(text);
        ImGui::PopTextWrapPos();
        ImGui::PopStyleColor();
        gui->pop_font();

        ImGui::EndGroup();
        ImGui::PopStyleVar();

        const ImVec2 wp = ImGui::GetWindowPos();
        const ImVec2 sz = ImGui::GetWindowSize();

        const ImVec2 glow_pad = ImVec2(SCALE(2), SCALE(2));
        draw->rect(dl, wp - glow_pad, wp + sz + glow_pad, draw->get_clr(accent_border, 0.28f), SCALE(14), draw_flags_round_corners_all, 1.0f);

        window_size = gui->window_size();
    }
    gui->end();
    gui->pop_color(2);
    gui->pop_var(4);

    return window_size;
}
