// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ItemBase.h"

UItemBase::UItemBase()
{
}

UItemBase* UItemBase::CreateItemCopy() const
{
	// 新しいアイテムを作成、コピーして返却
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

	ItemCopy->ID = this->ID;
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemQuality = this->ItemQuality;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemTextData = this->ItemTextData;
	ItemCopy->ItemNumericData = this->ItemNumericData;
	ItemCopy->ItemAssetData = this->ItemAssetData;

	return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, ItemNumericData.bIsStackable ? ItemNumericData.MaxStackSize : 1);
	}
}

void UItemBase::Use()
{
}