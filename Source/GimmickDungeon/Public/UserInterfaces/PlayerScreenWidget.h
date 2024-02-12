// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerScreenWidget.generated.h"


class UInventoryWidget;
class UFloorWidget;
/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API UPlayerScreenWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UFloorWidget* FloorWidget;
	
};
