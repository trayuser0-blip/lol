#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <Windows.h>
#include <array>
#include <memory>
#include "../../utils/settings/settings.hpp"

using config_color = std::array<float, 4>;

class c_config_manager {
public:
    c_config_manager();
    
    void save(std::string name);
    void load(std::string name);
    void remove(std::string name);
    void rename(std::string old_name, std::string new_name);
    void refresh_list();
    
    std::vector<std::string> config_list;
    char config_name[64] = "";
    
private:
    std::string folder;
    
    void write_bool(const char* section, const char* name, bool value);
    void write_int(const char* section, const char* name, int value);
    void write_float(const char* section, const char* name, float value);
    void write_color(const char* section, const char* name, config_color value);

    config_color read_color(
        const char* section,
        const char* name,
        config_color default_val
    );
    bool read_bool(const char* section, const char* name, bool default_val);
    int read_int(const char* section, const char* name, int default_val);
    float read_float(const char* section, const char* name, float default_val);
};

extern std::unique_ptr<c_config_manager> config_mgr;
