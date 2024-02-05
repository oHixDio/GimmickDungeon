// Fill out your copyright notice in the Description page of Project Settings.


#include <Kismet/GameplayStatics.h>
#include "CPP_A_RoomChangeDoor.h"

// Sets default values
ACPP_A_RoomChangeDoor::ACPP_A_RoomChangeDoor()
	:Super()
{
	RoomChangeDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Component"));
	RootComponent = RoomChangeDoorMesh;
}

// Called when the game starts or when spawned
void ACPP_A_RoomChangeDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_A_RoomChangeDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACPP_A_RoomChangeDoor::Interact(AActor* InteractActor)
{
	if (!Super::Interact(InteractActor)) { return false; }
	// ‘JˆÚ‚·‚éLevel‚ðLoad‚·‚é
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LoadLevel);
	return true;
}

