// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnim.generated.h"

/**
 * 
 */
UCLASS()
class FPSINGLEVR_API UMonsterAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movements", meta = (AllowPrivateAccess = "true"))
	class AMonsterBase* Monster;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movements", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movements", meta = (AllowPrivateAccess = "true"))
	bool bIsDead;

public:
	FORCEINLINE void SetbIsDead(bool IsDead) { bIsDead = IsDead; }

};
