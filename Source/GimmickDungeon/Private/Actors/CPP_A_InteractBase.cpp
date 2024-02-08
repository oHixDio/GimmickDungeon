// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CPP_A_InteractBase.h"

ACPP_A_InteractBase::ACPP_A_InteractBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Root Mesh");
	SetRootComponent(Mesh);
	Mesh->SetCustomDepthStencilValue(1);
}

void ACPP_A_InteractBase::BeginPlay()
{
	Super::BeginPlay();

}

void ACPP_A_InteractBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_A_InteractBase::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginInteract"));
}

void ACPP_A_InteractBase::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact!"));
}

void ACPP_A_InteractBase::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("EndInteract"));
}

void ACPP_A_InteractBase::BeginFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void ACPP_A_InteractBase::EndFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

