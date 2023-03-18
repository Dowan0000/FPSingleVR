// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnim.h"
#include "MonsterBase.h"

void UMonsterAnim::NativeInitializeAnimation()
{
	Monster = Cast<AMonsterBase>(TryGetPawnOwner());

	Speed = 0.f;
	
	bIsDead = false;
}

void UMonsterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Monster == nullptr)
	{
		Monster = Cast<AMonsterBase>(TryGetPawnOwner());
	}
	if (Monster)
	{
		Speed = Monster->GetVelocity().Size();
		
	}

}
