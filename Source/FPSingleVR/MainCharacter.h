// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ST_Machine.h"
#include "MainCharacter.generated.h"

UCLASS()
class FPSINGLEVR_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void HandRGrip(float Value);
	void HandLGrip(float Value);

	void UpDown(float Value);
	void LeftRight(float Value);

	void GrabRight();
	void ReleaseRight();

	void GrabLeft();
	void ReleaseLeft();

	void PressFire();

	AActor* FindNearestWeapon(class USkeletalMeshComponent* Hand);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateGoldWidget();

	void PressA();

	void ReleaseA();

	UFUNCTION(BlueprintCallable)
	void MachineLevelUp();

	void SetMachineDamage();

	UFUNCTION()
	void OnCapsuleBegineOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CameraRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* MCR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* MCL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* HandR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* HandL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class AWeaponBase* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	int32 CurGold;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetInteractionComponent* WidgetInteraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* InteractionMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Machine", meta = (AllowPrivateAccess = "true"))
	int MachineLevel;

	FMachineStruct* ST_Machine;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Machine", meta = (AllowPrivateAccess = "true"))
	class UDataTable* MachineData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Machine", meta = (AllowPrivateAccess = "true"))
	class AMachineBase* Machine;

public:
	void GetGold(int Gold);

	void SetVisibleInteractionMesh();

	void SetInVisibleInteractionMesh();

};
