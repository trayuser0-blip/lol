#include "../headers/functions.h"
#include "../headers/widgets.h"

void c_widgets::begin_child(std::string_view name, std::string_view icon_fa)
{
    struct child_state
    {
        float height{ 0 };
        float width{ 0 };
    };

    ImGuiWindow* window = gui->get_window();
    const ImVec2 pos = window->DC.CursorPos + SCALE(0, elements->child.name);
    const ImVec2 title_min = window->DC.CursorPos;
    const float name_h = SCALE(elements->child.name);
    const ImVec2 title_max = title_min + ImVec2((gui->content_max().x - var->style.item_spacing.x - var->style.window_padding.x) / 2.f, name_h);

    child_state* anim = gui->anim_container<child_state>(window->GetID(name.data()));
    anim->width = (gui->content_max().x - var->style.item_spacing.x - var->style.window_padding.x) / 2.f;
    draw->rect_filled(gui->window_drawlist(), pos, pos + ImVec2(anim->width, anim->height), draw->get_clr(clr->window.child), SCALE(elements->child.rounding));
    draw->rect(gui->window_drawlist(), pos, pos + ImVec2(anim->width, anim->height), draw->get_clr(clr->window.rect), SCALE(elements->child.rounding));

    if (icon_fa.empty()) {
        draw->text_clipped(gui->window_drawlist(), font->get(inter_medium_data, 14), title_min, title_max, draw->get_clr(clr->widgets.text_inactive), name.data(), NULL, NULL, ImVec2(0.f, 0.5f));
    } else {
        ImFont* ic_font = font->get(icon_data, 13);
        const float gap = SCALE(6);
        const float pad_l = SCALE(4);
        const float icon_col_w = SCALE(20);
        const ImVec2 icon_col_min(title_min.x + pad_l, title_min.y);
        const ImVec2 icon_col_max(title_min.x + pad_l + icon_col_w, title_max.y);
        draw->text_clipped(gui->window_drawlist(), ic_font, icon_col_min, icon_col_max, draw->get_clr(clr->accent), icon_fa.data(), icon_fa.data() + icon_fa.size(), NULL, ImVec2(0.5f, 0.42f));
        const ImVec2 text_min(title_min.x + pad_l + icon_col_w + gap, title_min.y);
        draw->text_clipped(gui->window_drawlist(), font->get(inter_medium_data, 14), text_min, title_max, draw->get_clr(clr->widgets.text_inactive), name.data(), NULL, NULL, ImVec2(0.f, 0.5f));
    }
    gui->push_var(style_var_window_padding, SCALE(elements->child.padding,0));
    gui->set_screen_pos(pos, pos_all);
    gui->begin_def_child(name.data() + std::string("content_child"), ImVec2(anim->width, anim->height), 0, window_flags_always_use_window_padding | window_flags_no_move | window_flags_nav_flattened | window_flags_no_saved_settings | window_flags_no_scrollbar);
    gui->push_var(style_var_item_spacing, SCALE(0,1));

    anim->height = gui->get_window()->ContentSize.y;
}

void c_widgets::end_child()
{
    gui->pop_var();
    gui->end_def_child();
    gui->pop_var();
}