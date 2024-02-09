// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/CPP_O_ItemBase.h"

UCPP_O_ItemBase::UCPP_O_ItemBase()
{
}

UCPP_O_ItemBase* UCPP_O_ItemBase::CreateItemCopy() const
{
	// 新しいアイテムを作成、コピーして返却
	UCPP_O_ItemBase* ItemCopy = NewObject<UCPP_O_ItemBase>(StaticClass());

	ItemCopy->ID = this->ID;
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemQuality = this->ItemQuality;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemTextData = this->ItemTextData;
	ItemCopy->ItemNumericData = this->ItemNumericData;
	ItemCopy->ItemStatistics = this->ItemStatistics;
	ItemCopy->ItemAssetData = this->ItemAssetData;\

	return ItemCopy;
}

void UCPP_O_ItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, ItemNumericData.bIsStackable ? ItemNumericData.MaxStackSize : 1);
	}
}

void UCPP_O_ItemBase::Use()
{
}
