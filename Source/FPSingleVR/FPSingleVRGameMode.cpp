// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSingleVRGameMode.h"
#include "FPSingleVRHUD.h"
#include "FPSingleVRCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSingleVRGameMode::AFPSingleVRGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSingleVRHUD::StaticClass();
}
