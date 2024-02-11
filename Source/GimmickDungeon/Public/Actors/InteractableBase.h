// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/InteractInterface.h"
#include "InteractableBase.generated.h"

UCLASS()
class GIMMICKDUNGEON_API AInteractableBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh{ nullptr };

	UPROPERTY(EditInstanceOnly, Category = "Interact Base")
	FInteractData InstanceInteractData;

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	AInteractableBase();

protected:
	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void BeginPlay() override;

	virtual void BeginInteract() override;
	virtual void Interact(AActor* InteractableActor) override;
	virtual void EndInteract() override;
	virtual void BeginFocus() override;
	virtual void EndFocus() override;

public:
	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void Tick(float DeltaTime) override;

};
