#include "config_manager.h"
#include "../../sdk/sdk.hpp"
#include <fstream>
#include <shlobj.h>

std::unique_ptr<c_config_manager> config_mgr = std::make_unique<c_config_manager>();

c_config_manager::c_config_manager() {
    folder = "C:\\FortMeme\\Configs";
    if (!std::filesystem::exists(folder)) {
        std::filesystem::create_directories(folder);
    }
    refresh_list();
}

void c_config_manager::refresh_list() {
    config_list.clear();
    for (const auto& entry : std::filesystem::directory_iterator(folder)) {
        if (entry.path().extension() == ".ini") {
            config_list.push_back(entry.path().stem().string());
        }
    }
}

void c_config_manager::remove(std::string name) {
    std::string path = folder + "\\" + name + ".ini";
    std::filesystem::remove(path);
    refresh_list();
}

void c_config_manager::rename(std::string old_name, std::string new_name) {
    std::string old_path = folder + "\\" + old_name + ".ini";
    std::string new_path = folder + "\\" + new_name + ".ini";
    if (std::filesystem::exists(old_path)) {
        std::filesystem::rename(old_path, new_path);
        refresh_list();
    }
}

void c_config_manager::write_bool(const char* section, const char* name, bool value) {
    WritePrivateProfileStringA(section, name, value ? "true" : "false", (folder + "\\" + config_name + ".ini").c_str());
}

void c_config_manager::write_int(const char* section, const char* name, int value) {
    WritePrivateProfileStringA(section, name, std::to_string(value).c_str(), (folder + "\\" + config_name + ".ini").c_str());
}

void c_config_manager::write_float(const char* section, const char* name, float value) {
    WritePrivateProfileStringA(section, name, std::to_string(value).c_str(), (folder + "\\" + config_name + ".ini").c_str());
}

void c_config_manager::write_color(const char* section, const char* name, flinearcolor value) {
    std::string color_str = std::to_string(value.r) + "," + std::to_string(value.g) + "," + std::to_string(value.b) + "," + std::to_string(value.a);
    WritePrivateProfileStringA(section, name, color_str.c_str(), (folder + "\\" + config_name + ".ini").c_str());
}

bool c_config_manager::read_bool(const char* section, const char* name, bool default_val) {
    char result[16];
    GetPrivateProfileStringA(section, name, default_val ? "true" : "false", result, 16, (folder + "\\" + config_name + ".ini").c_str());
    return (strcmp(result, "true") == 0);
}

int c_config_manager::read_int(const char* section, const char* name, int default_val) {
    return GetPrivateProfileIntA(section, name, default_val, (folder + "\\" + config_name + ".ini").c_str());
}

float c_config_manager::read_float(const char* section, const char* name, float default_val) {
    char result[32];
    GetPrivateProfileStringA(section, name, std::to_string(default_val).c_str(), result, 32, (folder + "\\" + config_name + ".ini").c_str());
    return std::stof(result);
}

flinearcolor c_config_manager::read_color(const char* section, const char* name, flinearcolor default_val) {
    char result[128];
    std::string def_str = std::to_string(default_val.r) + "," + std::to_string(default_val.g) + "," + std::to_string(default_val.b) + "," + std::to_string(default_val.a);
    GetPrivateProfileStringA(section, name, def_str.c_str(), result, 128, (folder + "\\" + config_name + ".ini").c_str());
    
    flinearcolor color = default_val;
    std::stringstream ss(result);
    std::string segment;
    std::vector<std::string> seg_list;
    while (std::getline(ss, segment, ',')) seg_list.push_back(segment);
    
    if (seg_list.size() == 4) {
        color.r = std::stof(seg_list[0]);
        color.g = std::stof(seg_list[1]);
        color.b = std::stof(seg_list[2]);
        color.a = std::stof(seg_list[3]);
    }
    return color;
}

void c_config_manager::save(std::string name) {
    strcpy_s(config_name, name.c_str());
    
    // Aimbot
    write_bool("Aimbot", "Mouse", settings::aimbot::mouse);
    write_bool("Aimbot", "Silent", settings::aimbot::silent);
    write_float("Aimbot", "MouseSpeed", settings::aimbot::mouse_speed);
    write_float("Aimbot", "FOV", settings::aimbot::field_of_view);
    write_bool("Aimbot", "ShowFOV", settings::aimbot::show_fov);
    write_bool("Aimbot", "TargetLine", settings::aimbot::target_line);
    write_int("Aimbot", "AimBone", settings::bones::aim_bone);
    write_bool("Aimbot", "VisibleOnly", settings::aimbot::visible_only);
    write_bool("Aimbot", "Prediction", settings::aimbot::prediction);
    write_bool("Aimbot", "Triggerbot", settings::aimbot::triggerbot);
    write_bool("Aimbot", "TriggerbotConstant", settings::aimbot::triggerbot_constant);
    write_bool("Aimbot", "TriggerbotHold", settings::aimbot::triggerbot_left_shift);
    write_int("Aimbot", "TriggerbotKey", settings::aimbot::triggerbot_key);

    // Visuals - Players
    write_bool("Player", "Box", settings::player::box);
    write_int("Player", "BoxType", settings::player::box_type);
    write_bool("Player", "Skeleton", settings::player::skeleton);
    write_bool("Player", "Snapline", settings::player::snapline);
    write_int("Player", "SnaplineType", settings::player::snapline_type);
    write_bool("Player", "Name", settings::player::player_name);
    write_bool("Player", "Platform", settings::player::platform);
    write_bool("Player", "ActiveWeapon", settings::player::active_weapon);
    write_bool("Player", "Distance", settings::player::display_distance);
    write_float("Player", "MaxDist", settings::player::max_distance);
    write_color("Player", "VisibleCol", settings::player::visible_color);
    write_color("Player", "InvisibleCol", settings::player::invisible_color);

    // Visuals - World/Misc
    write_bool("World", "Containers", settings::containers::chest);
    write_bool("World", "AmmoBoxes", settings::containers::ammo_box);
    write_bool("World", "ContainerChams", settings::containers::chams);
    write_int("World", "ContainerStencilID", settings::containers::container_stencil_id);
    write_bool("World", "Vehicles", settings::miscactors::vehicles);
    write_bool("World", "VehicleChams", settings::miscactors::vehicle_chams);
    write_int("World", "VehicleStencilID", settings::miscactors::vehicle_stencil_id);
    write_bool("World", "Rifts", settings::miscactors::rifts);
    write_bool("World", "Flags", settings::miscactors::flags);
    write_bool("World", "Traps", settings::miscactors::traps);
    write_float("World", "WorldDist", settings::world::max_distance);
    write_float("World", "ChamsDist", settings::world::chams_distance);
    
    // Pickups
    write_bool("Pickups", "Common", settings::pickups::common);
    write_bool("Pickups", "Uncommon", settings::pickups::uncommon);
    write_bool("Pickups", "Rare", settings::pickups::rare);
    write_bool("Pickups", "Epic", settings::pickups::epic);
    write_bool("Pickups", "Legendary", settings::pickups::legendary);
    write_bool("Pickups", "Mythic", settings::pickups::mythic);
    write_float("Pickups", "PickupDist", settings::pickups::max_distance);

    write_bool("Exploits", "Enable", settings::miscellaneous::enable_exploits);
    write_bool("Exploits", "VehicleFly", settings::miscellaneous::vehiclefly);
    write_float("Exploits", "VehicleFlySpeed", settings::miscellaneous::vehicle_flight_speed);
    write_bool("Exploits", "VehicleSpinbot", settings::miscellaneous::vehiclespinbot);
    write_float("Exploits", "VehicleSpinSpeed", settings::miscellaneous::vehiclespinspeed);
    write_bool("Exploits", "VehicleTPAura", settings::miscellaneous::Vehicle_TP_Aura);
    write_bool("Exploits", "InstantReload", settings::miscellaneous::instant_reload);
    write_bool("Exploits", "SpeedHack", settings::miscellaneous::speedhack);
    write_float("Exploits", "SpeedValue", settings::miscellaneous::speedhackslider);
    write_bool("Exploits", "AimbotBypass", settings::miscellaneous::aimbot_bypass);
    write_bool("Exploits", "NoRecoil", settings::miscellaneous::no_recoil);
    write_bool("Exploits", "TraceThroughWalls", settings::miscellaneous::enable_trace_through);
    write_bool("Exploits", "FOVChanger", settings::miscellaneous::fovchanger);
    write_float("Exploits", "FOVValue", settings::miscellaneous::fovslider);
    write_bool("Exploits", "TPose", settings::miscellaneous::tpose);
    write_bool("Exploits", "DoublePump", settings::miscellaneous::doublepump);
    write_bool("Exploits", "CobraSlice", settings::miscellaneous::cobra_slice);

    // Style
    write_bool("Misc", "TextOutlined", settings::style::text_outlined);
    write_bool("Misc", "PerfMode", settings::style::performance);
    write_bool("Misc", "LineBlackOutline", settings::style::line_black_outline);
    write_float("Misc", "LineOutlinePad", settings::style::line_outline_pad);
    write_float("Misc", "EspLineThickness", settings::style::esp_line_thickness);
    write_float("Misc", "GeometryLineThickness", settings::style::geometry_line_thickness);
    write_int("Misc", "FovCircleSegments", settings::style::fov_circle_segments);
    write_color("Misc", "FovCircleColor", settings::style::fov_circle_color);

    write_bool("Chams", "PlayerEnabled", settings::miscellaneous::chams_enabled);
    write_bool("Chams", "WeaponEnabled", settings::miscellaneous::weapon_chams_enabled);
    write_int("Chams", "Material", settings::miscellaneous::chams_material);
    write_float("Chams", "Emissive", settings::miscellaneous::chams_emissive);
    write_color("Chams", "PlayerColor", settings::miscellaneous::chams_color);
    write_color("Chams", "WeaponColor", settings::miscellaneous::weapon_chams_color);
    write_bool("Chams", "Wireframe", settings::miscellaneous::chams_wireframe);
    write_bool("Chams", "IgnoreDepth", settings::miscellaneous::chams_ignore_depth);
    write_bool("Chams", "TwoSided", settings::miscellaneous::chams_two_sided);
    write_bool("Chams", "VisibleOnly", settings::miscellaneous::chams_visible_only);
    write_bool("Chams", "LocalPlayer", settings::miscellaneous::chams_local_player);
    write_bool("Chams", "DynAreaLight", settings::miscellaneous::chams_dynamic_area_light);

    refresh_list();
}

void c_config_manager::load(std::string name) {
    strcpy_s(config_name, name.c_str());
    std::string path = folder + "\\" + name + ".ini";
    if (!std::filesystem::exists(path)) return;

    // Aimbot
    settings::aimbot::mouse = read_bool("Aimbot", "Mouse", settings::aimbot::mouse);
    settings::aimbot::silent = read_bool("Aimbot", "Silent", settings::aimbot::silent);
    settings::aimbot::mouse_speed = read_float("Aimbot", "MouseSpeed", settings::aimbot::mouse_speed);
    settings::aimbot::field_of_view = read_float("Aimbot", "FOV", settings::aimbot::field_of_view);
    settings::aimbot::show_fov = read_bool("Aimbot", "ShowFOV", settings::aimbot::show_fov);
    settings::aimbot::target_line = read_bool("Aimbot", "TargetLine", settings::aimbot::target_line);
    settings::bones::aim_bone = read_int("Aimbot", "AimBone", settings::bones::aim_bone);
    settings::aimbot::visible_only = read_bool("Aimbot", "VisibleOnly", settings::aimbot::visible_only);
    settings::aimbot::prediction = read_bool("Aimbot", "Prediction", settings::aimbot::prediction);
    settings::aimbot::triggerbot = read_bool("Aimbot", "Triggerbot", settings::aimbot::triggerbot);
    settings::aimbot::triggerbot_constant = read_bool("Aimbot", "TriggerbotConstant", settings::aimbot::triggerbot_constant);
    settings::aimbot::triggerbot_left_shift = read_bool("Aimbot", "TriggerbotHold", settings::aimbot::triggerbot_left_shift);
    settings::aimbot::triggerbot_key = read_int("Aimbot", "TriggerbotKey", settings::aimbot::triggerbot_key);

    // Visuals - Players
    settings::player::box = read_bool("Player", "Box", settings::player::box);
    settings::player::box_type = read_int("Player", "BoxType", settings::player::box_type);
    settings::player::skeleton = read_bool("Player", "Skeleton", settings::player::skeleton);
    settings::player::snapline = read_bool("Player", "Snapline", settings::player::snapline);
    settings::player::snapline_type = read_int("Player", "SnaplineType", settings::player::snapline_type);
    settings::player::player_name = read_bool("Player", "Name", settings::player::player_name);
    settings::player::platform = read_bool("Player", "Platform", settings::player::platform);
    settings::player::active_weapon = read_bool("Player", "ActiveWeapon", settings::player::active_weapon);
    settings::player::display_distance = read_bool("Player", "Distance", settings::player::display_distance);
    settings::player::max_distance = read_float("Player", "MaxDist", settings::player::max_distance);
    settings::player::visible_color = read_color("Player", "VisibleCol", settings::player::visible_color);
    settings::player::invisible_color = read_color("Player", "InvisibleCol", settings::player::invisible_color);

    // Visuals - World/Misc
    settings::containers::chest = read_bool("World", "Containers", settings::containers::chest);
    settings::containers::ammo_box = read_bool("World", "AmmoBoxes", settings::containers::ammo_box);
    settings::containers::chams = read_bool("World", "ContainerChams", settings::containers::chams);
    settings::containers::container_stencil_id = read_int("World", "ContainerStencilID", settings::containers::container_stencil_id);
    settings::miscactors::vehicles = read_bool("World", "Vehicles", settings::miscactors::vehicles);
    settings::miscactors::vehicle_chams = read_bool("World", "VehicleChams", settings::miscactors::vehicle_chams);
    settings::miscactors::vehicle_stencil_id = read_int("World", "VehicleStencilID", settings::miscactors::vehicle_stencil_id);
    settings::miscactors::rifts = read_bool("World", "Rifts", settings::miscactors::rifts);
    settings::miscactors::flags = read_bool("World", "Flags", settings::miscactors::flags);
    settings::miscactors::traps = read_bool("World", "Traps", settings::miscactors::traps);
    settings::world::max_distance = read_float("World", "WorldDist", settings::world::max_distance);
    settings::world::chams_distance = read_float("World", "ChamsDist", settings::world::chams_distance);

    // Pickups
    settings::pickups::common = read_bool("Pickups", "Common", settings::pickups::common);
    settings::pickups::uncommon = read_bool("Pickups", "Uncommon", settings::pickups::uncommon);
    settings::pickups::rare = read_bool("Pickups", "Rare", settings::pickups::rare);
    settings::pickups::epic = read_bool("Pickups", "Epic", settings::pickups::epic);
    settings::pickups::legendary = read_bool("Pickups", "Legendary", settings::pickups::legendary);
    settings::pickups::mythic = read_bool("Pickups", "Mythic", settings::pickups::mythic);
    settings::pickups::max_distance = read_float("Pickups", "PickupDist", settings::pickups::max_distance);

    settings::miscellaneous::enable_exploits = read_bool("Exploits", "Enable", settings::miscellaneous::enable_exploits);
    settings::miscellaneous::vehiclefly = read_bool("Exploits", "VehicleFly", settings::miscellaneous::vehiclefly);
    settings::miscellaneous::vehicle_flight_speed = read_float("Exploits", "VehicleFlySpeed", settings::miscellaneous::vehicle_flight_speed);
    settings::miscellaneous::speedhack = read_bool("Exploits", "SpeedHack", settings::miscellaneous::speedhack);
    settings::miscellaneous::speedhackslider = read_float("Exploits", "SpeedValue", settings::miscellaneous::speedhackslider);
    settings::miscellaneous::aimbot_bypass = read_bool("Exploits", "AimbotBypass", settings::miscellaneous::aimbot_bypass);
    settings::miscellaneous::no_recoil = read_bool("Exploits", "NoRecoil", settings::miscellaneous::no_recoil);
    settings::miscellaneous::vehiclespinbot = read_bool("Exploits", "VehicleSpinbot", settings::miscellaneous::vehiclespinbot);
    settings::miscellaneous::vehiclespinspeed = read_float("Exploits", "VehicleSpinSpeed", settings::miscellaneous::vehiclespinspeed);
    settings::miscellaneous::Vehicle_TP_Aura = read_bool("Exploits", "VehicleTPAura", settings::miscellaneous::Vehicle_TP_Aura);
    settings::miscellaneous::instant_reload = read_bool("Exploits", "InstantReload", settings::miscellaneous::instant_reload);
    settings::miscellaneous::enable_trace_through = read_bool("Exploits", "TraceThroughWalls", settings::miscellaneous::enable_trace_through);
    settings::miscellaneous::fovchanger = read_bool("Exploits", "FOVChanger", settings::miscellaneous::fovchanger);
    settings::miscellaneous::fovslider = read_float("Exploits", "FOVValue", settings::miscellaneous::fovslider);
    settings::miscellaneous::tpose = read_bool("Exploits", "TPose", settings::miscellaneous::tpose);
    settings::miscellaneous::doublepump = read_bool("Exploits", "DoublePump", settings::miscellaneous::doublepump);
    settings::miscellaneous::cobra_slice = read_bool("Exploits", "CobraSlice", settings::miscellaneous::cobra_slice);

    // Style
    settings::style::text_outlined = read_bool("Misc", "TextOutlined", settings::style::text_outlined);
    settings::style::performance = read_bool("Misc", "PerfMode", settings::style::performance);
    settings::style::line_black_outline = read_bool("Misc", "LineBlackOutline", settings::style::line_black_outline);
    settings::style::line_outline_pad = read_float("Misc", "LineOutlinePad", settings::style::line_outline_pad);
    settings::style::esp_line_thickness = read_float("Misc", "EspLineThickness", settings::style::esp_line_thickness);
    settings::style::geometry_line_thickness = read_float("Misc", "GeometryLineThickness", settings::style::geometry_line_thickness);
    {
        int s = read_int("Misc", "FovCircleSegments", settings::style::fov_circle_segments);
        if (s < 8) s = 8;
        if (s > 256) s = 256;
        settings::style::fov_circle_segments = s;
    }
    settings::style::fov_circle_color = read_color("Misc", "FovCircleColor", flinearcolor(1.f, 1.f, 1.f, 1.f));

    settings::miscellaneous::chams_enabled = read_bool("Chams", "PlayerEnabled", settings::miscellaneous::chams_enabled);
    settings::miscellaneous::weapon_chams_enabled = read_bool("Chams", "WeaponEnabled", settings::miscellaneous::weapon_chams_enabled);
    {
        int m = read_int("Chams", "Material", settings::miscellaneous::chams_material);
        if (m < 0) m = 0;
        if (m > 4) m = 4;
        settings::miscellaneous::chams_material = m;
    }
    settings::miscellaneous::chams_emissive = read_float("Chams", "Emissive", settings::miscellaneous::chams_emissive);
    settings::miscellaneous::chams_color = read_color("Chams", "PlayerColor", flinearcolor(0.25f, 0.85f, 1.f, 1.f));
    settings::miscellaneous::weapon_chams_color = read_color("Chams", "WeaponColor", flinearcolor(1.f, 0.45f, 0.9f, 1.f));
    settings::miscellaneous::chams_wireframe = read_bool("Chams", "Wireframe", settings::miscellaneous::chams_wireframe);
    settings::miscellaneous::chams_ignore_depth = read_bool("Chams", "IgnoreDepth", settings::miscellaneous::chams_ignore_depth);
    settings::miscellaneous::chams_two_sided = read_bool("Chams", "TwoSided", settings::miscellaneous::chams_two_sided);
    settings::miscellaneous::chams_visible_only = read_bool("Chams", "VisibleOnly", settings::miscellaneous::chams_visible_only);
    settings::miscellaneous::chams_local_player = read_bool("Chams", "LocalPlayer", settings::miscellaneous::chams_local_player);
    settings::miscellaneous::chams_dynamic_area_light = read_bool("Chams", "DynAreaLight", settings::miscellaneous::chams_dynamic_area_light);
}
