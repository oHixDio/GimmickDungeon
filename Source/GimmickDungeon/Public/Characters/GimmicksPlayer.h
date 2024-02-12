// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GimmickDungeonCharacter.h"
#include "InputActionValue.h"
#include "GimmicksPlayer.generated.h"


class UInputAction;

/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API AGimmicksPlayer : public AGimmickDungeonCharacter
{
	GENERATED_BODY()

public:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================


	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	AGimmicksPlayer();

	

protected:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================

	//==========================================================================================
	// Components
	//==========================================================================================
	UPROPERTY(EditAnywhere, Category = "Character | Component")
	class UInteractableComponent* Interactable{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Character | Component")
	class UInventoryComponent* Inventory{ nullptr };
	//==========================================================================================
	// Assets
	//==========================================================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	UInputAction* InteractAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	UInputAction* InventoryScrollAction{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	UInputAction* InventoryOneAction{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	UInputAction* InventoryTwoAction{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	UInputAction* InventoryThreeAction{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	UInputAction* InventoryFourAction{ nullptr };

	//==========================================================================================
	// Others
	//==========================================================================================

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
};