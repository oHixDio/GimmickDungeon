// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Data/ItemDataStructs.h>

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
	FItemData ItemData;

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	UItemBase();

	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy() const;

protected:
	bool operator==(const FName& OtherName) const
	{
		return this->ItemData.Name == OtherName;
	}
};
