// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"

// Sets default values
AMonsterBase::AMonsterBase() : 
	Health(100.f), MaxHealth(100.f)

{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMonsterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float AppliedDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	AppliedDamage = FMath::Min(Health, AppliedDamage);
	Health -= AppliedDamage;

	if (Health <= 0)
	{
		//dead
	}

	return AppliedDamage;
}

