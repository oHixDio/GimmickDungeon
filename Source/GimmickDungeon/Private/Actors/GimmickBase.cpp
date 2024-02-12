// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorComponents/ItemComponent.h"
#include "Objects/ItemBase.h"
#include "Actors/GimmickBase.h"

AGimmickBase::AGimmickBase()
{
	PrimaryActorTick.bCanEverTick = true;
	ItemComp = CreateDefaultSubobject<UItemComponent>("Item Component");
}

void AGimmickBase::BeginPlay()
{
	Super::BeginPlay();

	// 全てのMeshコンポーネントを取得
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

	UpdataInteractData();
}

void AGimmickBase::UpdataInteractData()
{
	if (!ItemComp->GetItemDataReference()) { return; }

	UItemBase* Item = ItemComp->GetItemDataReference();

	InteractData.InteractType = EInteractType::Gimmick;
	InteractData.Name = FText::FromName(Item->ItemData.Name);
	InteractData.Quantity = ItemComp->GetQuantity();
	InteractData.InteractableDuration = GimmickData.InteractDuration;
}

void AGimmickBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AGimmickBase::BeginFocus()
{
	for (UPrimitiveComponent* Mesh : MeshList)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void AGimmickBase::EndFocus()
{
	for (UPrimitiveComponent* Mesh : MeshList)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void AGimmickBase::BeginInteract()
{
}

void AGimmickBase::Interact(AActor* InteractableActor)
{
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *InteractableActor->GetActorNameOrLabel());
}

void AGimmickBase::EndInteract()
{
}
