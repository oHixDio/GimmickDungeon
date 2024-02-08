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


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	class UInputAction* InteractAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	class UInputAction* PickupAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input|State")
	float FocusRange = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Input|State")
	AActor* LastFocusActor = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Input|State")
	TArray<AActor*> FounndItemActorList;

private:
	bool bFocusGimmick = false;

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
	void Interact(const FInputActionValue& Value);

	void Pickup(const FInputActionValue& Value);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
