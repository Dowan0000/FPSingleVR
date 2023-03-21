// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreBase.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "MainCharacter.h"

// Sets default values
AStoreBase::AStoreBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Scene);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Mesh);

	StoreWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("StoreWidget"));
	StoreWidget->SetupAttachment(Scene);

}

// Called when the game starts or when spawned
void AStoreBase::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AStoreBase::BoxBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AStoreBase::BoxEndOverlap);

}

void AStoreBase::BoxBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Character = Cast<AMainCharacter>(OtherActor);
	if (Character)
	{
		Character->SetVisibleInteractionMesh();
	}
}

void AStoreBase::BoxEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Character)
	{
		Character->SetInVisibleInteractionMesh();
	}
}

