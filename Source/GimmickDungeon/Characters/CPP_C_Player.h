// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./GimmickDungeonCharacter.h"
#include "InputActionValue.h"
#include "CPP_C_Player.generated.h"

/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API ACPP_C_Player : public AGimmickDungeonCharacter
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	class UInputAction* InteractAction = nullptr;

	float FocusRange = 100.f;

	AActor* LastFocusActor;
	
public:
	ACPP_C_Player();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void FocusChecker();

protected:
	void Interact(const FInputActionValue& Value );
};
