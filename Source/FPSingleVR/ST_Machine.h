#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ST_Machine.generated.h"

USTRUCT(BlueprintType)
struct FMachineStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int UpgradePrice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Machine1Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Machine2Damage;
};