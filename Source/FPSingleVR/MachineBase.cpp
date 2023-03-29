// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineBase.h"
#include "MonsterBase.h"
#include "MachineBullet.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"

// Sets default values
AMachineBase::AMachineBase() : 
	Damage(10.f), AttackSpeed(3.f)

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AMachineBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(BulletTimer, this, &AMachineBase::SpawnBullet, AttackSpeed, true, 1.f);

}

void AMachineBase::FindNearestMonster()
{
	TArray<AActor*> TargetMonsters;
	CollisionBox->GetOverlappingActors(TargetMonsters);

	float NearestDist = 10'000.f;
	AMonsterBase* NearestMonster = nullptr;

	for (AActor* Target : TargetMonsters)
	{
		AMonsterBase* IsMonster = Cast<AMonsterBase>(Target);
		if (IsMonster == nullptr) continue;

		float Dist = UKismetMathLibrary::Vector_Distance(
			GetActorLocation(), IsMonster->GetActorLocation());

		if (NearestDist > Dist)
		{
			NearestDist = Dist;
			NearestMonster = IsMonster;
		}
	}

	if (NearestMonster)
		TargetMonster = NearestMonster;
	
}

void AMachineBase::SpawnBullet()
{
	FindNearestMonster();

	if (TargetMonster == nullptr) return;

	if (MachineBullet)
	{
		FVector Location = FVector(GetActorLocation().X, 
			GetActorLocation().Y, GetActorLocation().Z + 50.f);

		SpawnedBullet = GetWorld()->SpawnActor<AMachineBullet>(MachineBullet,
			Location, GetActorRotation());

		if (SpawnedBullet && TargetMonster)
		{
			SpawnedBullet->SetMachine(this);
			SpawnedBullet->SetTargetEnemy(TargetMonster);
		}
	}
	
}
