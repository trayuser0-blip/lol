#pragma once
#include "sdk/vector.hpp"

struct flinearcolor;


#ifdef DEFINE_GLOBALS
#define GLOBAL_VAR(type, name, value) type name = value
#define GLOBAL_VAR_NOINIT(type, name) type name
#else
#define GLOBAL_VAR(type, name, value) extern type name
#define GLOBAL_VAR_NOINIT(type, name) extern type name
#endif

namespace settings {
	namespace bones
	{
		GLOBAL_VAR(int, aim_bone, 0); // 0 = Head, 1 = Neck, 2 = Chest, 3 = Pelvis
	}

	namespace aimbot {

		GLOBAL_VAR(bool,  enable,        true);
		GLOBAL_VAR(int,   aim_key,       VK_RBUTTON);
		GLOBAL_VAR(bool,  memory,        false);
		GLOBAL_VAR(bool,  mouse,         false);
		GLOBAL_VAR(bool,  silent,        false);
		GLOBAL_VAR(bool,  sticky_silent, false);
		GLOBAL_VAR(bool,  interpolate,   false);
		GLOBAL_VAR(bool,  constant,      false);
		GLOBAL_VAR(bool,  show_fov,      false);
		GLOBAL_VAR(bool,  visible_only,  false);
		GLOBAL_VAR(bool,  target_line,   false);
		GLOBAL_VAR(float, mouse_speed,   5.f);
		GLOBAL_VAR(float, interpolate_speed, 5.f);
		GLOBAL_VAR(float, field_of_view, 100.f);
		GLOBAL_VAR(bool,  prediction,    false);
		GLOBAL_VAR(bool,  triggerbot,    false);
		GLOBAL_VAR(bool,  triggerbot_constant, false);
		GLOBAL_VAR(bool,  triggerbot_left_shift, false);
		GLOBAL_VAR(int,   triggerbot_key, 0); // ImGuiKey enum value for custom hold-key
	}

	namespace player {
		GLOBAL_VAR(bool,  enable,           true);
		GLOBAL_VAR(bool,  skeleton,         false);
		GLOBAL_VAR(bool,  box,              true);
		GLOBAL_VAR(int,   box_type,         0);    
		GLOBAL_VAR(bool,  snapline,         false);
		GLOBAL_VAR(int,   snapline_type,    0);    
		GLOBAL_VAR(bool,  player_name,      false);
		GLOBAL_VAR(bool,  platform,         false);
		GLOBAL_VAR(bool,  active_weapon,    false);
		GLOBAL_VAR(bool,  display_distance, false);
		GLOBAL_VAR(float, max_distance,     300.f);
		GLOBAL_VAR_NOINIT(flinearcolor, visible_color);
		GLOBAL_VAR_NOINIT(flinearcolor, invisible_color);
	}

	namespace containers {
		GLOBAL_VAR(bool,  enable,           true);
		GLOBAL_VAR(bool,  chams,            false);
		GLOBAL_VAR(bool,  chams_chest,      false);
		GLOBAL_VAR(bool,  chams_ammo_box,   false);
		GLOBAL_VAR_NOINIT(flinearcolor, chams_chest_color);
		GLOBAL_VAR_NOINIT(flinearcolor, chams_ammo_box_color);
		GLOBAL_VAR(bool,  display_distance, true);
		GLOBAL_VAR(bool,  lines,            false);
		GLOBAL_VAR(bool,  chest,            false);
		GLOBAL_VAR(bool,  ammo_box,         false);
		GLOBAL_VAR(bool,  cooler_and_food,  false);
		GLOBAL_VAR(bool,  safe,             false);
		GLOBAL_VAR(float, line_offset,      20.f);
		GLOBAL_VAR(int,   container_stencil_id, 1); // 0 = Blue, 1 = Red, 2 = Yellow
	}

	namespace pickups {
		GLOBAL_VAR(bool,  enable,           true);
		GLOBAL_VAR(float, max_distance,     150.f);
		GLOBAL_VAR(bool,  display_distance, true);
		GLOBAL_VAR(bool,  lines,            false);
		GLOBAL_VAR(bool,  common,           false);
		GLOBAL_VAR(bool,  uncommon,         false);
		GLOBAL_VAR(bool,  rare,             false);
		GLOBAL_VAR(bool,  epic,             false);
		GLOBAL_VAR(bool,  legendary,        false);
		GLOBAL_VAR(bool,  mythic,           false);
		GLOBAL_VAR(float, line_offset,      20.f);
	}

	namespace weakspot {
		GLOBAL_VAR(bool,  enable,          false);
		GLOBAL_VAR(bool,  weakspot_aimbot, false);
		GLOBAL_VAR(bool,  silent,          false);
		GLOBAL_VAR(bool,  interpolate,     false);
		GLOBAL_VAR(bool,  constant,        false);
		GLOBAL_VAR(bool,  target_line,     false);
		GLOBAL_VAR(float, interpolate_speed, 1.f);
	}



	namespace miscellaneous {
		GLOBAL_VAR(bool,  enable_exploits,     false);
		GLOBAL_VAR(bool,  chams_enabled,       false);
		GLOBAL_VAR(bool,  weapon_chams_enabled, false);
		GLOBAL_VAR(int,   chams_material,      2);
		GLOBAL_VAR(bool,  chams_visible_only,  false);
		GLOBAL_VAR(bool,  chams_local_player,  false);
		GLOBAL_VAR(bool,  chams_wireframe,     false);
		GLOBAL_VAR(bool,  chams_ignore_depth,  true);
		GLOBAL_VAR(bool,  chams_two_sided,     true);
		GLOBAL_VAR(bool,  chams_dynamic_area_light, false);
		GLOBAL_VAR_NOINIT(flinearcolor, chams_visible_color); // Deprecated
		GLOBAL_VAR_NOINIT(flinearcolor, chams_invisible_color); // Deprecated
		GLOBAL_VAR(float, chams_emissive,      500.0f);
		GLOBAL_VAR_NOINIT(flinearcolor, chams_color); // Player Chams Color
		GLOBAL_VAR_NOINIT(flinearcolor, weapon_chams_color); // Weapon Chams Color
		GLOBAL_VAR(bool,  ProjectileTP,        false);
		GLOBAL_VAR(bool,  Vehicle_Tp_To_Waypoint, false);
		GLOBAL_VAR(int,   Vehicle_Tp_Key,      VK_F8);
		GLOBAL_VAR(bool,  vehiclefly,          false);
		GLOBAL_VAR(float, vehicle_flight_speed, 50.f);

		GLOBAL_VAR(bool,  fovchanger,          false);
		GLOBAL_VAR(bool,  fullautoweapons,     false);
		GLOBAL_VAR(bool,  magicbullet,         false);
		GLOBAL_VAR(float, vehiclegravityslider, 0.01f);
		GLOBAL_VAR(bool,  doublepump,          false);
		GLOBAL_VAR(bool,  boatspeed,           false);
		GLOBAL_VAR(float, boatspeedslider,     10.f);
		GLOBAL_VAR(bool,  ziplinefly,          false);
		GLOBAL_VAR(bool,  testingthing,        false);
		GLOBAL_VAR(bool,  skinchanger_enabled, false);
		GLOBAL_VAR(bool,  steal_outfit,        false);
		GLOBAL_VAR(bool,  steal_weapon_camo,   false);
		GLOBAL_VAR(bool,  steal_pickaxe,       false);
		GLOBAL_VAR(uint64_t, skinchanger_target,  0);

		GLOBAL_VAR(bool,  creativefly,         false);
		GLOBAL_VAR(bool,  speedhack,           false);
		GLOBAL_VAR(bool,  instantrespawntest,  false);
		GLOBAL_VAR(bool,  vehiclespinbot,      false);
		GLOBAL_VAR(float, vehiclespinspeed,    5.f);
		GLOBAL_VAR(bool,  Vehicle_TP_Aura,     false);
		GLOBAL_VAR(bool,  enable_trace_through, false);
		GLOBAL_VAR(bool,  no_recoil,            false);
		GLOBAL_VAR(bool,  no_recoil_reset,      true);
		GLOBAL_VAR(bool,  instant_reload,       false);
		GLOBAL_VAR(bool,  instant_reload_reset, true);

		GLOBAL_VAR(bool,  ziplinetp,           false);
		GLOBAL_VAR(float, fovslider,           120.f);
		GLOBAL_VAR_NOINIT(Vector3, AddPlayerFlyLocation);
		GLOBAL_VAR_NOINIT(Vector3, SetLocation);
		GLOBAL_VAR_NOINIT(Vector3, vehiclelocation);
		GLOBAL_VAR(float, speedhackslider,     50.f);
		GLOBAL_VAR(bool,  aimbot_bypass,       true);
		GLOBAL_VAR(bool,  first_person,        false);
		GLOBAL_VAR(bool,  hover,               false);
		GLOBAL_VAR(bool,  skydiving,           false);
		GLOBAL_VAR(bool,  float_mode,          false);
		GLOBAL_VAR(bool,  tpose,               false);
		GLOBAL_VAR(bool,  tpose_reset,         true);
		GLOBAL_VAR(bool,  speedhack_reset,     true);
		GLOBAL_VAR(bool,  doublepump_reset,    true);
		GLOBAL_VAR(bool,  fovchanger_reset,    true);

		// Advanced Player Exploits (Batch 2)
		GLOBAL_VAR(bool,  instant_interact,     false); // Kept
		GLOBAL_VAR(bool,  fast_finish_interact, false); // Kept
		GLOBAL_VAR(bool,  modified_gravity,     false);
		GLOBAL_VAR(bool,  remote_hoist,         false);
		GLOBAL_VAR(bool,  remote_interrogate,   false);
		GLOBAL_VAR(bool,  add_attachment,       false);
		GLOBAL_VAR(bool,  remove_attachment,    false);
		GLOBAL_VAR(bool,  add_ignored_actor,    false);
		GLOBAL_VAR(bool,  disable_cosmetic_swap, false);
		GLOBAL_VAR(bool,  detach_rc_pawn,       false);
		GLOBAL_VAR(bool,  force_end_zipline,    false);
		GLOBAL_VAR(bool,  water_hand_splash,    false);
		GLOBAL_VAR(bool,  water_jump_splash,    false);
		GLOBAL_VAR(bool,  max_impact_damage,    false);
		GLOBAL_VAR(float, damage_multiplier,     10.f);
		GLOBAL_VAR(bool,  vehicle_god_mode,     false);
		GLOBAL_VAR(bool,  server_choose_part,   false);
		GLOBAL_VAR(bool,  server_color_cycle,   false);
		GLOBAL_VAR(bool,  server_equip_last,    false);
		GLOBAL_VAR(bool,  server_eject_zipline, false);
		GLOBAL_VAR(bool,  assembled_cosmetic,   false);
		GLOBAL_VAR(bool,  set_balloon_rope,     false);
		GLOBAL_VAR(bool,  destroy_balloon_rope, false);
		GLOBAL_VAR(bool,  set_chute_action,     false);
		GLOBAL_VAR(bool,  height_adjust_target, false);
		GLOBAL_VAR(bool,  facial_override,      false);
		GLOBAL_VAR(bool,  camera_rel_move,      false);
		GLOBAL_VAR(bool,  never_skip_anim,      false);
		GLOBAL_VAR(bool,  multi_balloon_hack,   false);
		GLOBAL_VAR(int,   balloon_count,        3);
		GLOBAL_VAR(bool,  pending_sky_launch,   false);
		GLOBAL_VAR(bool,  pending_tether_launch, false);
		GLOBAL_VAR(bool,  set_pet_type,         false);
		GLOBAL_VAR(bool,  transform_montage,    false);
		GLOBAL_VAR(bool,  swap_cosmetic_id,     false);
		GLOBAL_VAR(bool,  unequip_weapon_id,    false);
		GLOBAL_VAR(bool,  push_anim_bp,         false);
		GLOBAL_VAR(bool,  cobra_slice,          false);
		GLOBAL_VAR(int,   cobra_slice_key,      VK_F1);
	}
	
	namespace rifts {
		GLOBAL_VAR(bool, enable,           false);
		GLOBAL_VAR(bool, display_distance, false);
	}

	namespace miscactors {
		GLOBAL_VAR(bool, enable,           true);
		GLOBAL_VAR(bool, display_distance, true);
		GLOBAL_VAR(bool, vehicles,         false);
		GLOBAL_VAR(bool, vehicle_chams,    false);
		GLOBAL_VAR(bool, rifts,            false);
		GLOBAL_VAR(bool, flags,            false);
		GLOBAL_VAR(bool, traps,            false);
		GLOBAL_VAR(int,   vehicle_stencil_id, 1); // 0 = Blue, 1 = Red, 2 = Yellow

	}
	namespace vehicles {
		GLOBAL_VAR(bool, enable,           false);
		GLOBAL_VAR(bool, display_distance, false);
	}

	namespace style {
		GLOBAL_VAR(bool, text_outlined, true);
		GLOBAL_VAR(bool, performance, false);
		GLOBAL_VAR(bool, line_black_outline, false);
		GLOBAL_VAR(float, line_outline_pad, 1.f);
		GLOBAL_VAR(float, esp_line_thickness, 1.f);
		GLOBAL_VAR(float, geometry_line_thickness, 2.f);
		GLOBAL_VAR(int, fov_circle_segments, 96);
		GLOBAL_VAR_NOINIT(flinearcolor, fov_circle_color);
	}
	namespace world {
		GLOBAL_VAR(float, max_distance, 150.f);
		GLOBAL_VAR(float, chams_distance, 150.f);
	}

} 

#undef GLOBAL_VAR
#undef GLOBAL_VAR_NOINIT
