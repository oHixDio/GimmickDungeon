// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GimmickDungeonCharacter.h"
#include "InputActionValue.h"
#include "CPP_C_Player.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GIMMICKDUNGEON_API ACPP_C_Player : public AGimmickDungeonCharacter
{
	GENERATED_BODY()

public:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================


	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	ACPP_C_Player();

protected:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	class UInputAction* InteractAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	class UInputAction* TestInteractableAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	class UInputAction* PickupAction = nullptr;
	//==========================================================================================
	// Components
	//==========================================================================================
	UPROPERTY(EditAnywhere)
	class UCPP_AC_Interactable* InteractableComp{ nullptr };
	//==========================================================================================
	// Assets
	//==========================================================================================

	//==========================================================================================
	// Others
	//==========================================================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input|State")
	float FocusRange = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Input|State")
	AActor* LastFocusActor = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Input|State")
	TArray<AActor*> FounndItemActorList;


	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Interact(const FInputActionValue& Value);

	void Pickup(const FInputActionValue& Value);

private:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	bool bFocusGimmick = false;

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	void FocusChecker();
};
