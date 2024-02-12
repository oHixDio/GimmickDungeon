// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"


class UTextBlock;
class UImage;
class UBorder;
/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void UpdateWidget(const struct FInteractData* InteractData) const;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Inventory Widget | Item Data")
	UTextBlock* QuantityText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Inventory Widget | Item Data")
	UImage* Icon;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Inventory Widget | Item Data")
	UBorder* SlotFrame;

	bool bIsSelect;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
};
