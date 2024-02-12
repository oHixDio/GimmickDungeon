// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


class UInventorySlotWidget;
/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventorySlotWidget* Slot_0;
	UInventorySlotWidget* Slot_1;
	UInventorySlotWidget* Slot_2;
	UInventorySlotWidget* Slot_3;

	TArray<UInventorySlotWidget*> SlotList = { Slot_0,Slot_1,Slot_2,Slot_3 };

};
