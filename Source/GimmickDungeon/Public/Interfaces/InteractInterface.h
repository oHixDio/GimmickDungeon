// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UENUM()
enum class EInteractType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	Gimmick UMETA(DisplayName = "Gimmick"),
	NonPlayerCharacter UMETA(DisplayName = "NonPlayerCharacter"),
};

USTRUCT()
struct FInteractData
{
	GENERATED_USTRUCT_BODY()

	FInteractData() :
		InteractType(EInteractType::Pickup),
		Name(FText::GetEmpty()),
		Quantity(0),
		InteractableDuration(0.0f)
	{

	};

	UPROPERTY(EditInstanceOnly)
	EInteractType InteractType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	int32 Quantity;

	UPROPERTY(EditInstanceOnly)
	float InteractableDuration;
};

UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class GIMMICKDUNGEON_API IInteractInterface
{
	GENERATED_BODY()

public:
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void Interact(AActor* InteractableActor);
	virtual void EndInteract();

	FInteractData InteractData;
};
