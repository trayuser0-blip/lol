#pragma once
#include <cstdint>
//

namespace offsets {
    constexpr std::uintptr_t StaticFindObject = 0x8D9F7D;
    constexpr std::uintptr_t ProcessEvent = 0x62DD6;
    constexpr std::uintptr_t GameViewPort = 0xAE0;
    constexpr std::uintptr_t UObject_FName = 0x18;

    // Mesh / Visuals
    constexpr std::uintptr_t BlendMode = 0x169;
    constexpr std::uintptr_t Wireframe = 0x208;
    constexpr std::uintptr_t TwoSided = 0x1b8;
    constexpr std::uintptr_t bDisableDepthTest = 0x1f0;
    constexpr std::uintptr_t bUseEmissiveForDynamicAreaLighting = 0x1f0;
    constexpr std::uintptr_t Mesh = 0x330;
    constexpr std::uintptr_t PawnMaterials_ALL = 0x62E0;
    constexpr std::uintptr_t SkeletalMeshes = 0x6320;
    constexpr std::uintptr_t PawnBodyMaterials = 0x62E8;
    constexpr std::uintptr_t PawnHeadMaterials = 0x62D8;
    constexpr std::uintptr_t PawnHatMaterials = 0x62C8;
    constexpr std::uintptr_t PawnBackpackMaterials = 0x62B8;
    constexpr std::uintptr_t CosmeticLoadoutPC = 0x1FC8;
    constexpr std::uintptr_t CosmeticLoadoutPC_Character = 0x2000; // CosmeticLoadoutPC + 0x38

    // Weapon / Combat
    constexpr std::uintptr_t LastFiredLocation = 0x5c10;
    constexpr std::uintptr_t LastFiredDirection = 0x5c28;
    constexpr std::uintptr_t bCurrentlyShooting = 0x53a;
    constexpr std::uintptr_t bIsFiring = 0x1361;
    constexpr std::uintptr_t WeaponAnimInstance = 0x400;
    constexpr std::uintptr_t TimeRemainingForBulletSpread = 0x2540;
    constexpr std::uintptr_t BulletCountForPerBulletSpread = 0x253c;
    constexpr std::uintptr_t FirstShotAccuracyMinWaitTime = 0x252c;
    constexpr std::uintptr_t WeaponMeshes = 0xfe0;
    constexpr std::uintptr_t TargetSourceOffset = 0x1108;
    constexpr std::uintptr_t TargetSourceOffsetWhileCrouched = 0x1120;
    constexpr std::uintptr_t TargetSourceOffsetWhileTargeting = 0x1138;
    constexpr std::uintptr_t GlobalAnimRateScale = 0xaa8;
    constexpr std::uintptr_t bIsReloadingWeapon = 0x3b9;
    constexpr std::uintptr_t bIgnoreTryToFireSlotCooldownRestriction = 0x1889;
    constexpr std::uintptr_t WeaponAbilitySystemComponent = 0x1a00; // FortWeapon -> FortAbilitySystemComponent*

    // AbilitySystemComponent
    constexpr std::uintptr_t ASC_SpawnedAttributes = 0x1070; // TArray<UAttributeSet*>

    // FortWeaponAttrSet – spread attribute field offsets (each is FortGameplayAttributeData)
    // FGameplayAttributeData layout (with vtable): BaseValue @ +0x08, CurrentValue @ +0x0C
    // FortGameplayAttributeData extras:           UnclampedBaseValue @ +0x1C, UnclampedCurrentValue @ +0x20
    constexpr std::uintptr_t AttrSet_WeaponSpreadReduction         = 0x0f8;
    constexpr std::uintptr_t AttrSet_WeaponCrouchingSpreadMult     = 0x2d8;
    constexpr std::uintptr_t AttrSet_WeaponSlidingSpreadMult       = 0x300;
    constexpr std::uintptr_t AttrSet_WeaponSpreadDownsightsMult    = 0x238;
    // FGameplayAttributeData field offsets within the struct
    constexpr std::uintptr_t AttrData_BaseValue                    = 0x08;
    constexpr std::uintptr_t AttrData_CurrentValue                 = 0x0C;
    constexpr std::uintptr_t AttrData_UnclampedBase                = 0x1C;
    constexpr std::uintptr_t AttrData_UnclampedCurrent             = 0x20;
    
    // Actor / Component
    constexpr std::uintptr_t RootComponent = 0x1b0;
    constexpr std::uintptr_t Relative_Location = 0x140;

    // Camera aimbot
    constexpr std::uintptr_t ViewPitchMin = 0x28ec;
    constexpr std::uintptr_t ViewPitchMax = 0x28f0;
    constexpr std::uintptr_t ViewYawMin = 0x28f4;
    constexpr std::uintptr_t ViewYawMax = 0x28f8;
    constexpr std::uintptr_t timedialation = 0x68;

    // Vehicle
    constexpr std::uintptr_t CachedFuelComponent = 0x13b0;
    constexpr std::uintptr_t CurrentVehicle = 0x2d10;
    constexpr std::uintptr_t VehicleMinHorSpeedToDamage = 0xf48;
    constexpr std::uintptr_t VehicleMaxHorSpeedToDamage = 0xf4c;
    constexpr std::uintptr_t VehicleMinHorSpeedDamage = 0xf50;
    constexpr std::uintptr_t VehicleMaxHorSpeedDamage = 0xf54;
    constexpr std::uintptr_t PushForceCurrentMultiplier = 0xb94;

    // Pawn / Player
    constexpr std::uintptr_t bForceRefpose = 0xac1;
    constexpr std::uintptr_t PlayerState = 0x2d0;
    constexpr std::uintptr_t PawnPrivate = 0x358;

    // World / GameState
    constexpr std::uintptr_t GameState = 0x1d8;
    constexpr std::uintptr_t PlayerArray = 0x2c8;

    // Controller
    constexpr std::uintptr_t InputPitchScale = 0x54c;
    constexpr std::uintptr_t InputYawScale = 0x548;
    constexpr std::uintptr_t TargetedFortPawn = 0x1840;

    // Canvas
    constexpr std::uintptr_t ClipX = 0x30;
    constexpr std::uintptr_t ClipY = 0x34;

    // Component / Engine
    constexpr std::uintptr_t LocalPlayers = 0x38;
    constexpr std::uintptr_t ViewportClient_LocalPlayer = 0x78;
    constexpr std::uintptr_t World_ViewportClient = 0x78;
    constexpr std::uintptr_t EngineFont = 0x70;

    // Item / Pickup
    constexpr std::uintptr_t ItemDisplayName = 0x38;
    constexpr std::uintptr_t PrimaryPickupItemEntry = 0x3A8;

    // Building
    constexpr std::uintptr_t bAlreadySearched = 0xd0a;
    constexpr std::uintptr_t bActive = 0x2e0;

    // Cosmetic Loadout Component
    constexpr std::uintptr_t CosmeticLoadoutVal = 0xc8;
    constexpr std::uintptr_t ActiveArchetypes = 0xd8;
    constexpr std::uintptr_t CachedAthenaLoadoutUnrestricted = 0xe8;
    constexpr std::uintptr_t CachedAthenaLoadout_Comp = 0x280;
    constexpr std::uintptr_t WeaponDefinition = 0x5e8;
    constexpr std::uintptr_t WeaponMeshOverride = 0xe8;

    // ESP Info
    constexpr std::uintptr_t CurrentCharXP = 0x424;
    constexpr std::uintptr_t InitialExperienceLevel = 0x424;
    
}
