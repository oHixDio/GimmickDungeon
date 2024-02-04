// Fill out your copyright notice in the Description page of Project Settings.

#include <Components/SphereComponent.h>
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_A_ItemBase.h"

// Sets default values
ACPP_A_ItemBase::ACPP_A_ItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerDetectComp = CreateDefaultSubobject<USphereComponent>(TEXT("Root Comp"));
	RootComponent = PlayerDetectComp;
	PlayerDetectComp->SetSphereRadius(DetectRadius);
}

// Called when the game starts or when spawned
void ACPP_A_ItemBase::BeginPlay()
{
	Super::BeginPlay();
	UNiagaraFunctionLibrary::SpawnSystemAttached(ItemNiagaraSystem, RootComponent, TEXT(""), GetActorLocation(), GetActorRotation(), EAttachLocation::KeepWorldPosition, true);
}

// Called every frame
void ACPP_A_ItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* ACPP_A_ItemBase::Found()
{
	return nullptr;
}

AActor* ACPP_A_ItemBase::Lost()
{
	return nullptr;
}

FName ACPP_A_ItemBase::Pickup()
{
	Destroy();
	return Name;
}

