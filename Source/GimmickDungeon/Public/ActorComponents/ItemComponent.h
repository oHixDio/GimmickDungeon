// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "Components/ActorComponent.h"
#include "ItemComponent.generated.h"

class UItemBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GIMMICKDUNGEON_API UItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	


	// Sets default values for this component's properties
	UItemComponent();

	FORCEINLINE UItemBase* GetItemDataReference() const { return ItemDataReference; }
	FORCEINLINE int32 GetQuantity() const { return Quantity; }

protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle ItemID;

	UPROPERTY(EditAnywhere)
	int32 Quantity;

	UPROPERTY(VisibleAnywhere)
	UItemBase* ItemDataReference;

	// Called when the game starts
	virtual void BeginPlay() override;

	void InitializeData();

};
