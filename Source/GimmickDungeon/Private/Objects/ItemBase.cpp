// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ItemBase.h"

UItemBase::UItemBase()
{
}

UItemBase* UItemBase::CreateItemCopy() const
{
	// �V�����A�C�e�����쐬�A�R�s�[���ĕԋp
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

	ItemCopy->ItemData.ItemType = this->ItemData.ItemType;
	ItemCopy->ItemData.Name = this->ItemData.Name;
	ItemCopy->ItemData.Description = this->ItemData.Description;
	ItemCopy->ItemData.MaxStackSize = this->ItemData.MaxStackSize;
	ItemCopy->ItemData.InventoryIcon = this->ItemData.InventoryIcon;
	ItemCopy->ItemData.SpawnableClass = this->ItemData.SpawnableClass;

	return ItemCopy;
}
