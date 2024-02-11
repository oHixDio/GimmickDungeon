// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Data/ItemDataStructs.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	int32 Quantity;

	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	FName ID;

	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	FItemNumericData ItemNumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	FItemAssetData ItemAssetData;

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	UItemBase();

	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy() const;

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * ItemNumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return ItemNumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == ItemNumericData.MaxStackSize; };

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use();

protected:
	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}
};
