
#include "../headers/includes.h"
#include "../headers/widgets.h"
#include "../../../utils/settings/settings.hpp"
#include <algorithm>
#include <vector>
#include <string>

void c_search::search()
{
	if (search_element.empty()) return;

	std::string lower_search = search_element;
	std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), ::tolower);

	auto check = [&](std::string_view name) {
		std::string lower_name = std::string(name);
		std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);
		return lower_name.find(lower_search) != std::string::npos;
	};

	// --- AIMBOT ---
	if (check("Enable Camera Aimbot")) widgets->checkbox_ptr("Enable Camera Aimbot", &settings::aimbot::mouse);
	if (check("Silent Aim")) widgets->checkbox_ptr("Silent Aim", &settings::aimbot::silent);
	if (check("Smoothing")) widgets->slider_float_ptr("Smoothing", &settings::aimbot::mouse_speed, 1.f, 25.f);
	if (check("FOV Value")) widgets->slider_float_ptr("FOV Value", &settings::aimbot::field_of_view, 10.f, 500.f);
	if (check("Show FOV Circle")) widgets->checkbox_ptr("Show FOV Circle", &settings::aimbot::show_fov);
	if (check("Target Line")) widgets->checkbox_ptr("Target Line", &settings::aimbot::target_line);

	// --- TRIGGERBOT ---
	if (check("Triggerbot")) widgets->checkbox_ptr("Triggerbot", &settings::aimbot::triggerbot);
	if (check("Constant")) {
		if (widgets->checkbox_ptr("Constant (always fire)", &settings::aimbot::triggerbot_constant).value_changed && settings::aimbot::triggerbot_constant) {
			settings::aimbot::triggerbot_left_shift = false;
		}
	}
	if (check("Hold Key Mode")) {
		if (widgets->checkbox_ptr("Hold Key Mode", &settings::aimbot::triggerbot_left_shift).value_changed && settings::aimbot::triggerbot_left_shift) {
			settings::aimbot::triggerbot_constant = false;
		}
	}

	// --- PLAYER VISUALS ---
	if (check("Box")) widgets->checkbox_ptr("Box", &settings::player::box);
	if (check("Snapline")) widgets->checkbox_ptr("Snapline", &settings::player::snapline);
	if (check("Skeleton")) widgets->checkbox_ptr("Skeleton", &settings::player::skeleton);
	if (check("Distance")) widgets->checkbox_ptr("Distance", &settings::player::display_distance);
	if (check("Weapon")) widgets->checkbox_ptr("Weapon", &settings::player::active_weapon);
	if (check("Username")) widgets->checkbox_ptr("Username", &settings::player::player_name);
	if (check("Platform")) widgets->checkbox_ptr("Platform", &settings::player::platform);
	if (check("Render Distance")) widgets->slider_float_ptr("Render Distance", &settings::player::max_distance, 5.f, 300.f, "%.0fm");

	// --- CHAMS ---

	if (check("Container Stencil")) widgets->checkbox_ptr("Container Stencil", &settings::containers::chams);
	if (check("Vehicle Chams")) widgets->checkbox_ptr("Vehicle Chams", &settings::miscactors::vehicle_chams);

	// --- EXPLOITS / MISC ---
	if (check("Speed Exploit (Hover)")) widgets->checkbox_ptr("Speed Exploit (Hover)", &settings::miscellaneous::speedhack);
	if (check("Speed Value")) widgets->slider_float_ptr("Speed Value", &settings::miscellaneous::speedhackslider, 1.f, 500.f);
	if (check("Aimbot Bypass")) widgets->checkbox_ptr("Aimbot Bypass", &settings::miscellaneous::aimbot_bypass);
	if (check("Bullet Teleport")) widgets->checkbox_ptr("Bullet Teleport", &settings::miscellaneous::ProjectileTP);
	if (check("No Recoil")) widgets->checkbox_ptr("No Recoil", &settings::miscellaneous::no_recoil);

	if (check("Instant Reload")) widgets->checkbox_ptr("Instant Reload", &settings::miscellaneous::instant_reload);
	if (check("Trace Through Walls")) widgets->checkbox_ptr("Trace Through Walls", &settings::miscellaneous::enable_trace_through);
	if (check("Vehicle Spinbot")) widgets->checkbox_ptr("Vehicle Spinbot", &settings::miscellaneous::vehiclespinbot);
	if (check("Spin Speed")) widgets->slider_float_ptr("Spin Speed", &settings::miscellaneous::vehiclespinspeed, 0.5f, 30.f);
	if (check("Vehicle TP Aura")) widgets->checkbox_ptr("Vehicle TP Aura", &settings::miscellaneous::Vehicle_TP_Aura);
	if (check("FOV Changer")) widgets->checkbox_ptr("FOV Changer", &settings::miscellaneous::fovchanger);
	if (check("FOV")) widgets->slider_float_ptr("FOV", &settings::miscellaneous::fovslider, 60.f, 170.f);

	// --- SKINCHANGER ---
	if (check("Skinchanger Enable")) widgets->checkbox_ptr("Enable Skinchanger", &settings::miscellaneous::skinchanger_enabled);
	if (check("Steal Outfit")) widgets->checkbox_ptr("Steal Outfit", &settings::miscellaneous::steal_outfit);
	if (check("Steal Weapon Camo")) widgets->checkbox_ptr("Steal Weapon Camo", &settings::miscellaneous::steal_weapon_camo);
	if (check("Steal Pickaxe")) widgets->checkbox_ptr("Steal Pickaxe", &settings::miscellaneous::steal_pickaxe);
}