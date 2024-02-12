// Fill out your copyright notice in the Description page of Project Settings.



#include "Objects/ItemBase.h"
#include <Data/ItemDataStructs.h>
#include "ActorComponents/ItemComponent.h"

// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeData();
}

void UItemComponent::InitializeData()
{
	if (ItemID.IsNull()) { return; }

	const FItemData* ItemCopy = ItemID.DataTable->FindRow<FItemData>(ItemID.RowName, ItemID.RowName.ToString());

	if (!ItemCopy) { return; }

	ItemDataReference = NewObject<UItemBase>(this, UItemBase::StaticClass());
	ItemDataReference->ItemData.ItemType = ItemCopy->ItemType;
	ItemDataReference->ItemData.Name = ItemCopy->Name;
	ItemDataReference->ItemData.Description = ItemCopy->Description;
	ItemDataReference->ItemData.MaxStackSize = ItemCopy->MaxStackSize;
	ItemDataReference->ItemData.InventoryIcon = ItemCopy->InventoryIcon;
	ItemDataReference->ItemData.SpawnableClass = ItemCopy->SpawnableClass;

	Quantity = FMath::Clamp(Quantity, 0, FMath::Min(Quantity, ItemDataReference->ItemData.MaxStackSize));
}