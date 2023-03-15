// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	
	SetRootComponent(WeaponMesh);
	CollisionBox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::SetItemCollision(EItemState State)
{
	switch (State)
	{
	case EItemState::EIS_Equipped:
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		WeaponMesh->SetSimulatePhysics(false);

		break;

	case EItemState::EIS_Falling:
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		
		WeaponMesh->SetSimulatePhysics(true);

		break;
	}
}

void AWeaponBase::SetItemState(EItemState NewItemState)
{
	ItemState = NewItemState;
	SetItemCollision(NewItemState);
}

