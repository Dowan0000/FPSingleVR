// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "MonsterAnim.h"
#include "MainCharacter.h"

// Sets default values
AMonsterBase::AMonsterBase() :
	Health(100.f), MaxHealth(100.f),
	bIsDead(false), MonsterGold(10)

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

	if (!bIsDead)
	{
		SetActorLocation(GetActorLocation() + GetActorForwardVector() * DeltaTime * 50.f);
	}	
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

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("%f"), Health));

	if (!bIsDead && Health <= 0)
	{
		MonsterAnim = Cast<UMonsterAnim>(GetMesh()->GetAnimInstance());
		if (MonsterAnim)
		{
			MonsterAnim->SetbIsDead(true);
			bIsDead = true;

			Character = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
			if (Character)
				Character->GetGold(MonsterGold);

			UpdateMonsterCount();

			GetWorldTimerManager().SetTimer(DestroyTimer, this,
				&AMonsterBase::DestroyMonster, 1.f);
		}

	}

	return AppliedDamage;
}

void AMonsterBase::DestroyMonster()
{
	Destroy();
}

void AMonsterBase::UpdateMonsterCount_Implementation()
{
}

