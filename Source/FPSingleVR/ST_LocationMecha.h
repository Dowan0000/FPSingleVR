#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ST_LocationMecha.generated.h"

USTRUCT(BlueprintType)
struct FLocMechaStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LocX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LocY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LocZ;

};