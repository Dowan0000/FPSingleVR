// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSingleVRHUD.generated.h"

UCLASS()
class AFPSingleVRHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPSingleVRHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

