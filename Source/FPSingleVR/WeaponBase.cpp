// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Bullet.h"
#include "Engine/DataTable.h"

// Sets default values
AWeaponBase::AWeaponBase() : 
	ItemState(EItemState::EIS_Falling),
	SocketName(""), BulletSocket(""),
	WeaponLevel(1), Damage(10.f),
	WeaponType(EWeaponType::None)

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	
	SetRootComponent(WeaponMesh);
	CollisionBox->SetupAttachment(RootComponent);

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	WeaponMesh->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetDamage();
}

void AWeaponBase::SetItemCollision(EItemState State)
{
	switch (State)
	{
	case EItemState::EIS_Equipped:
		WeaponMesh->SetSimulatePhysics(false);

		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		break;

	case EItemState::EIS_Falling:
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		
		WeaponMesh->SetSimulatePhysics(true);

		break;
	}
}

void AWeaponBase::PressShoot_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("sshotttttttttttttt"));
	
	const USkeletalMeshSocket* BulletSocketName = WeaponMesh->GetSocketByName(BulletSocket);
	if (BulletSocketName)
	{
		FTransform BulletSocketTransform = BulletSocketName->GetSocketTransform(WeaponMesh);
		
		Bullet = GetWorld()->SpawnActor<ABullet>(SpawnBullet, BulletSocketTransform);
		if (Bullet)
		{
			Bullet->SetWeapon(this);
		}
	}

}

void AWeaponBase::WeaponLevelUp()
{
	WeaponLevel++;
	SetDamage();
}

void AWeaponBase::SetDamage()
{
	FName RowName = FName(*FString::FromInt(WeaponLevel));
	ST_Weapon = WeaponData->FindRow<FWeaponStruct>(RowName, FString(""));

	switch (WeaponType)
	{
	case EWeaponType::None:
		
		break;

	case EWeaponType::Pistol:
		Damage = ST_Weapon->PistolDamage;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("settttttttt"));
		
		break;

	case EWeaponType::Rifle:
		Damage = ST_Weapon->RifleDamage;

		break;

	}

}

void AWeaponBase::SetItemState(EItemState NewItemState)
{
	ItemState = NewItemState;
	SetItemCollision(NewItemState);
}

