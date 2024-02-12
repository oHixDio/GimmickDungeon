// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GIMMICKDUNGEON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> Contents;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 InventorySize;

	// �󂫂����邩���ׂ�
	// void FindSlot();
	// �A�C�e����ǉ�����
	// void PushItem();
	// �A�C�e���������
	// void PullItem();
	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void BeginPlay() override;

};
