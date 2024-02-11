// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableBase.h"

AInteractableBase::AInteractableBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Root Mesh");
	SetRootComponent(Mesh);
	Mesh->SetCustomDepthStencilValue(1);
}

void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	InteractData = InstanceInteractData;
}

void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableBase::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginInteract"));
}

void AInteractableBase::Interact(AActor* InteractableActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact is %s!"), *InteractableActor->GetActorNameOrLabel());
}

void AInteractableBase::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("EndInteract"));
}

void AInteractableBase::BeginFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void AInteractableBase::EndFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}