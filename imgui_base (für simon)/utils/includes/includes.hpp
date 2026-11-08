#pragma once

#include <iostream>
#include <cstdint>
#include <Windows.h>

inline std::uintptr_t game = std::uintptr_t(0);

// Basic Utils
#include "utils/memory.hpp"
#include "utils/importer.hpp"
#include "utils/vmthook.hpp"

// SDK & Data
#include "sdk/vector.hpp"
#include "sdk/offsets/offsets.hpp"
#include "sdk/game_miscs.hpp"
#include "sdk/sdk.hpp"

// Core logic
#include "utils/settings/settings.hpp"
#include "game/Drawing/render.hpp"

// Game Features (Ultra Clean)
#include "utils/settings/globals.hpp"
#include "game/Aimbot/aimbot.hpp"
#include "game/Exploits/exploits.h"
#include "game/World-Esp/world_esp.h"
#include "game/Gameloop/gameloop.hpp"


// Hooks
#include "hooks/hooks.hpp"
