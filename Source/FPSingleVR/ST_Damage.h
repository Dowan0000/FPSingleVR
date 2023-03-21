#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ST_Damage.generated.h"

USTRUCT(BlueprintType)
struct FDamageStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float PistolDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float RifleDamage;

};