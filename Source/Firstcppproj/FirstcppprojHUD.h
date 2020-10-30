// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FirstcppprojHUD.generated.h"

UCLASS()
class AFirstcppprojHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFirstcppprojHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

