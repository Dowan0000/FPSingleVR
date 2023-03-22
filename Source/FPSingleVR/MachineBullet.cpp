// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "MonsterBase.h"
#include "MachineBase.h"

// Sets default values
AMachineBullet::AMachineBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	SetRootComponent(BulletMesh);
	BulletMesh->SetEnableGravity(false);

	BulletMovement = CreateAbstractDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
	BulletMovement->InitialSpeed = 1000.f;
	BulletMovement->MaxSpeed = 10'000.f;
	BulletMovement->bIsHomingProjectile = true;
	BulletMovement->HomingAccelerationMagnitude = 10'000.f;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	CapsuleCollision->SetupAttachment(BulletMesh);
	CapsuleCollision->SetEnableGravity(false);

	InitialLifeSpan = 5.f;
}

// Called when the game starts or when spawned
void AMachineBullet::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AMachineBullet::HitBullet);
}

void AMachineBullet::HitBullet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HittedMonster = Cast<AMonsterBase>(OtherActor);
	if (HittedMonster)
	{
		FDamageEvent DamageEvent;
		HittedMonster->TakeDamage(CurMachine->GetDamage(), DamageEvent,
			GetWorld()->GetFirstPlayerController(), this);

		Destroy();
	}
}

void AMachineBullet::SetMachine(AMachineBase* NewMachine)
{
	CurMachine = NewMachine;
}

void AMachineBullet::SetTargetEnemy(AMonsterBase* NewTarget)
{
	TargetEnemy = NewTarget;
}

