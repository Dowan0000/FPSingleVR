// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "MainAnim.h"

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

