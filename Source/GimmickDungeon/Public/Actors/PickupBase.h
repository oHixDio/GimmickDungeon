// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "PickupBase.generated.h"

/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API APickupBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(EditAnywhere)
	class UItemComponent* ItemComp;

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	APickupBase();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void Interact(AActor* InteractableActor)override;
	virtual void EndInteract() override;
};
