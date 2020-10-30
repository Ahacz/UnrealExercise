// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstcppprojGameMode.h"
#include "FirstcppprojHUD.h"
#include "FirstcppprojCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFirstcppprojGameMode::AFirstcppprojGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirstcppprojHUD::StaticClass();
}
