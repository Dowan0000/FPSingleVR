#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ST_Weapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int UpgradePrice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PistolDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RifleDamage;
};