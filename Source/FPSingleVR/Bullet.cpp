// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MonsterBase.h"
#include "WeaponBase.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	SetRootComponent(BulletMesh);

	BulletMovement = CreateAbstractDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
	BulletMovement->InitialSpeed = 10'000.f;
	BulletMovement->MaxSpeed = 10'000.f;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(BulletMesh);

	InitialLifeSpan = 5.f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABullet::HitBullet);

}

void ABullet::HitBullet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HittedMonster = Cast<AMonsterBase>(OtherActor);
	if (HittedMonster && CurWeapon)
	{
		FDamageEvent DamageEvent;
		HittedMonster->TakeDamage(CurWeapon->GetDamage(), DamageEvent,
			GetWorld()->GetFirstPlayerController(), this);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%f"), CurWeapon->GetDamage()));
	}

}

void ABullet::SetWeapon(AWeaponBase* NewWeapon)
{
	CurWeapon = NewWeapon;
}

//void ABullet::SetTargetEnemy(AMonsterBase* NewTarget)
//{
//	TargetEnemy = NewTarget;
//}
