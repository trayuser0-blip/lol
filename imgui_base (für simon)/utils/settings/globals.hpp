#pragma once
#include "../../sdk/sdk.hpp"

namespace fortnite {
	extern bool visible;
	extern struct skeleton player_skeleton;
	extern struct fvector aimbot_target_3d;
	extern bool target_visible;
	extern player_pawn* local_pawn;
	extern aplayercontroller* local_controller;

	namespace temp {
		extern bool silent_active;
		extern frotator silent_rotation;
		extern bool sticky_silent_active;
		extern frotator sticky_silent_rotation;
	}
}

// Global Definitions (Single Translation Unit)
#ifdef DEFINE_GLOBALS
namespace fortnite {
	bool visible = false;
	skeleton player_skeleton = skeleton();
	fvector aimbot_target_3d = fvector();
	bool target_visible = false;
	player_pawn* local_pawn = nullptr;
	aplayercontroller* local_controller = nullptr;

	namespace temp {
		bool silent_active = false;
		frotator silent_rotation = frotator();
		bool sticky_silent_active = false;
		frotator sticky_silent_rotation = frotator();
	}
}
#endif
