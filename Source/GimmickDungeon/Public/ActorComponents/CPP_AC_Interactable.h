// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_AC_Interactable.generated.h"

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractableActor(nullptr), LastInteractionCheckTime(0.0f)
	{

	};

	UPROPERTY()
	AActor* CurrentInteractableActor;

	UPROPERTY()
	float LastInteractionCheckTime;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GIMMICKDUNGEON_API UCPP_AC_Interactable : public UActorComponent
{
	GENERATED_BODY()

public:	
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	float FieldOfVision{0.0f};


	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	UCPP_AC_Interactable();

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
	TScriptInterface<class ICPP_I_Interact> TargetInteractableActor;

	float InteractionCheckFrequency{ 0.0f };

	float InteractionCheckDistance{ 1.0f };

	bool bShouldInteractionCheck{ false };

	FTimerHandle InteractionTimerHandle;
	
	FInteractionData InteractionData;
	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void BeginPlay() override;

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractableActor);
	void NoInteractableFound();
	// ICPP_I_Interactとは違うメソッド
	void Interact();
};
