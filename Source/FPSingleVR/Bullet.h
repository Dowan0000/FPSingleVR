// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class FPSINGLEVR_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HitBullet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BulletMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* BulletMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hit", meta = (AllowPrivateAccess = "true"))
	class AMonsterBase* HittedMonster;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class AWeaponBase* CurWeapon;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyLocation", meta = (AllowPrivateAccess = "true"))
	AMonsterBase* TargetEnemy;*/

public:
	void SetWeapon(AWeaponBase* NewWeapon);

	/*void SetTargetEnemy(AMonsterBase* NewTarget);*/

};
