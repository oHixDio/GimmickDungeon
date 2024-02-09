// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_I_Interact.generated.h"

UENUM()
enum class EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	Gimmick UMETA(DisplayName = "Gimmick"),
	NonPlayerCharacter UMETA(DisplayName = "NonPlayerCharacter"),
};

USTRUCT()
struct FInteractableData
{
	GENERATED_USTRUCT_BODY()

	FInteractableData():
	InteractableType(EInteractableType::Pickup),
	Name(FText::GetEmpty()),
	Action(FText::GetEmpty()),
	Quantity(0),
	InteractableDuration(0.0f)
	{

	};

	UPROPERTY(EditInstanceOnly)
	EInteractableType InteractableType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Action;

	UPROPERTY(EditInstanceOnly)
	int32 Quantity;

	UPROPERTY(EditInstanceOnly)
	float InteractableDuration;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_I_Interact : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GIMMICKDUNGEON_API ICPP_I_Interact
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginInteract();
	virtual void Interact();
	virtual void EndInteract();
	virtual void BeginFocus();
	virtual void EndFocus();

	FInteractableData InteractableData;
};