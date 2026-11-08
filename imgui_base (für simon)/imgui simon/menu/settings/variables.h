#pragma once
#include <string>
#include <vector>
#include "imgui.h"
#include "../headers/flags.h"
#include "../data/icons.h"

struct section_data
{
	std::string icon;
	std::string text;
};

struct IDirect3DDevice9;
struct ID3D11Device;
struct ID3D11DeviceContext;

class c_variables
{
public:
	struct
	{
		window_flags flags{ window_flags_no_saved_settings | window_flags_no_decoration | window_flags_no_scrollbar | window_flags_no_background };

		ImVec2 size{ 750, 478 };
		float rounding{ 16 };
		ImVec2 indent{ 0,0 };
		ImVec2 items_spacing{ 0,0 };

		float size_scrollbar{ 5 };
		ImVec2 margins_scrollbar{ 10,10 };
		float padding_scrollbar{ 10 };

	} window;

	struct
	{
		float dpi = 1.f;
		int stored_dpi = 100;
		bool dpi_changed = true;
		std::vector<section_data> sections{ { ICON_FA_CROSSHAIRS, "Aimbot" }, { ICON_FA_EYE, "Visuals" }, { ICON_FA_BOLT, "Exploits" }, { ICON_FA_SHIRT, "Skinchanger" }, { ICON_FA_FLOPPY_DISK, "Configs" }, { ICON_FA_GEARS, "Settings" } };

		int section_index;
		int previous_section_index{ -1 };
		float tab_alpha{ 0 };
		float tab_offset{ 0 };
		int active_section{ 0 };
		float section_alpha{ 0 };

		IDirect3DDevice9* g_pd3dDevice = nullptr;

		ImVec2 icon{ 21,22 };
		float line{ 21 };

		ImTextureID top_icon_texture;
		ImTextureID image_texture;
		ImTextureID background_texture;
		ImTextureID preview_texture;
		float preview_alpha{ 0 };
		ImVec2 preview_size{ 300, 450 };
		int preview_width, preview_height;

		std::string full_username = "user";
		std::string discord_name = "User";
		int selected_language = 0;

		bool settings_opened{ false };
		float settings_alpha{ 0 };
		bool settings_hovered{ false };
		ImVec2 settings_size{ 250, 151 };
		float settings_top{ 60 };

		float stored_color[4]{ -1.f, -1.f, -1.f, -1.f };

	} gui;

	ID3D11Device* device;
	ID3D11DeviceContext* context;

	gui_style style;

};

inline std::unique_ptr<c_variables> var = std::make_unique<c_variables>();
