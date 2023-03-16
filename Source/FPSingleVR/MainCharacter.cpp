// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "MainAnim.h"
#include "Kismet/KismetMathLibrary.h"
#include "WeaponBase.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	CameraRoot->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraRoot);

	MCR = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MCR"));
	MCL = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MCL"));
	
	MCR->SetupAttachment(CameraRoot);
	MCL->SetupAttachment(CameraRoot);

	MCR->SetTrackingMotionSource(FName("Right"));
	MCL->SetTrackingMotionSource(FName("Left"));

	//MCR->bDisplayDeviceModel = true;
	//MCL->bDisplayDeviceModel = true;

	HandR = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandR"));
	HandL = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandL"));
	
	HandR->SetupAttachment(MCR);
	HandL->SetupAttachment(MCL);

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("HandRGrip"), this, &AMainCharacter::HandRGrip);
	PlayerInputComponent->BindAxis(TEXT("HandLGrip"), this, &AMainCharacter::HandLGrip);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMainCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMainCharacter::LeftRight);

	PlayerInputComponent->BindAction(TEXT("GrabRight"), EInputEvent::IE_Pressed, this, &AMainCharacter::GrabRight);
	PlayerInputComponent->BindAction(TEXT("GrabRight"), EInputEvent::IE_Released, this, &AMainCharacter::ReleaseRight);
	
	PlayerInputComponent->BindAction(TEXT("GrabLeft"), EInputEvent::IE_Pressed, this, &AMainCharacter::GrabLeft);
	PlayerInputComponent->BindAction(TEXT("GrabLeft"), EInputEvent::IE_Released, this, &AMainCharacter::ReleaseLeft);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AMainCharacter::PressFire);

}

void AMainCharacter::HandRGrip(float Value)
{
	UMainAnim* MainAnim = Cast<UMainAnim>(HandR->GetAnimInstance());;

	if (Value != 0)
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("11111"));

	if (MainAnim == nullptr)
	{
		MainAnim = Cast<UMainAnim>(HandR->GetAnimInstance());
	}
	
	if (MainAnim)
	{
		MainAnim->GripValue = Value;
	}

}

void AMainCharacter::HandLGrip(float Value)
{
	UMainAnim* MainAnim = Cast<UMainAnim>(HandL->GetAnimInstance());;

	if (Value != 0)
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("22222"));

	if (MainAnim == nullptr)
	{
		MainAnim = Cast<UMainAnim>(HandL->GetAnimInstance());
	}

	if (MainAnim)
	{
		MainAnim->GripValue = Value;
	}

}

void AMainCharacter::UpDown(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMainCharacter::LeftRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMainCharacter::GrabRight()
{
	if (CurrentWeapon) return;

	AActor* NearestWeapon = FindNearestWeapon(HandR);
	if (NearestWeapon)
	{
		CurrentWeapon = Cast<AWeaponBase>(NearestWeapon);
		if (CurrentWeapon)
		{
			if (CurrentWeapon->GetSocketName() == FName("")) return;

			CurrentWeapon->SetItemState(EItemState::EIS_Equipped);

			CurrentWeapon->AttachToComponent(HandR, 
				FAttachmentTransformRules::SnapToTargetNotIncludingScale,
				CurrentWeapon->GetSocketName());
		}
	}
}

void AMainCharacter::ReleaseRight()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentWeapon->SetItemState(EItemState::EIS_Falling);
		CurrentWeapon = nullptr;
	}
}

void AMainCharacter::GrabLeft()
{
	//AActor* NearestWepon = FindNearestWeapon(HandL);
}

void AMainCharacter::ReleaseLeft()
{
}

void AMainCharacter::PressFire()
{
	if (CurrentWeapon == nullptr) return;

	IWeaponInterface* Interobj = Cast<IWeaponInterface>(CurrentWeapon);
	if (Interobj)
	{
		Interobj->Execute_PressShoot(CurrentWeapon);
	}
}

AActor* AMainCharacter::FindNearestWeapon(USkeletalMeshComponent* Hand)
{
	TArray<AActor*> OverlappingActors;
	Hand->GetOverlappingActors(OverlappingActors);

	float NearestDist = 10'000.f;
	AActor* NearestActor = nullptr;

	for (AActor* OverlappedActor : OverlappingActors)
	{
		IWeaponInterface* WeaponInterface = Cast<IWeaponInterface>(OverlappedActor);
		if (WeaponInterface == nullptr)
			continue;
		
		float Dist = UKismetMathLibrary::Vector_Distance(
			Hand->GetComponentLocation(), OverlappedActor->GetActorLocation());
	
		if (NearestDist > Dist)
		{
			NearestDist = Dist;
			NearestActor = OverlappedActor;
		}
	}

	if (NearestActor)
		return NearestActor;
	else
		return nullptr;
}

