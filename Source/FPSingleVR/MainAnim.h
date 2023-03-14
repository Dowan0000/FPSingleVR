// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnim.generated.h"

/**
 * 
 */
UCLASS()
class FPSINGLEVR_API UMainAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class AMainCharacter* Character;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HandGripValue")
	float GripValue;

};
