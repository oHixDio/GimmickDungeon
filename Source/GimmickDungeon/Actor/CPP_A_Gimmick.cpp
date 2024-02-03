// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_A_Gimmick.h"

// Sets default values
ACPP_A_Gimmick::ACPP_A_Gimmick()
	:Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACPP_A_Gimmick::BeginPlay()
{
	Super::BeginPlay();
	TArray<UActorComponent*> CompList = GetComponentsByClass(UPrimitiveComponent::StaticClass());
	for (UActorComponent* Comp : CompList)
	{
		if (UPrimitiveComponent* Mesh = Cast<UPrimitiveComponent>(Comp))
		{
			Mesh->SetRenderCustomDepth(false);
			Mesh->SetCustomDepthStencilValue(1);
			MeshList.Add(Mesh);
		}
	}
}

// Called every frame
void ACPP_A_Gimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_A_Gimmick::Focus()
{
	if (!bCanInteract) { return; }
	for (UPrimitiveComponent* Mesh : MeshList)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void ACPP_A_Gimmick::UnFocus()
{
	
	for (UPrimitiveComponent* Mesh : MeshList)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

bool ACPP_A_Gimmick::Interact(AActor* InteractActor)
{
	if (!bCanInteract) { return false; }
	if (bDoOnce) { bCanInteract = false; }
	if (bGimmickAccessOnly)
	{
		if (Cast<APawn>(InteractActor)) { return false; }
	}
	return true;
}

