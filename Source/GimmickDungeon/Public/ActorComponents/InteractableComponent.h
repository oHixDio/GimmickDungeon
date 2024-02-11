// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

USTRUCT()
struct FInteractableData
{
	GENERATED_USTRUCT_BODY()

	FInteractableData() :  LastInteractionCheckTime(0.0f) {};

	UPROPERTY()
	AActor* CurrentInteractableActor;

	UPROPERTY()
	float LastInteractionCheckTime;
};

class IInteractInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GIMMICKDUNGEON_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(VisibleAnywhere)
	FInteractableData InteractionData;

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	UInteractableComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE bool IsInteracting() const { return GetWorld()->GetTimerManager().IsTimerActive(InteractionTimerHandle); }

	void BeginInteract();
	void EndInteract();

protected:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	APawn* Owner;

	UPROPERTY(VisibleAnywhere, Category = "Character | Intertaction")
	TScriptInterface<IInteractInterface> TargetInteractableActor;

	// インタラクトアクタを検出する間隔頻度 
	float InteractionCheckFrequency{ 0.0f };

	// インタラクトアクタを検出する距離
	float InteractionCheckDistance{ 1.0f };

	FTimerHandle InteractionTimerHandle;
	
	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void BeginPlay() override;

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractableActor);
	void NoInteractableFound();
	void Interact();
};
