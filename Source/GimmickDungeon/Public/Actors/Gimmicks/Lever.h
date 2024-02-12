// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GimmickBase.h"
#include "Lever.generated.h"

/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API ALever : public AGimmickBase
{
	GENERATED_BODY()

public:
	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	ALever();
	virtual void Tick(float DeltaTime) override;

	void Interact(AActor* InteractableActor) override;

protected:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(EditAnywhere, Category = "Lever|Components")
	UStaticMeshComponent* LeverMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Lever|Components")
	UStaticMeshComponent* LeverFrameMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Lever|State")
	float PullMoveTimer = 1.f;

	UPROPERTY(VisibleAnywhere, Category = "Lever|State")
	bool bIsPulled = false;

	UPROPERTY(VisibleAnywhere, Category = "Lever|State")
	bool bSholudCountPullMoveTimer = false;

	UPROPERTY(VisibleAnywhere, Category = "Lever|State")
	FRotator CurRotate;

	UPROPERTY(VisibleAnywhere, Category = "Lever|State")
	float PullMoveElapsedTimer = 0.f;

	const float PULL_SCALE = 60.f;


	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Pull(AActor* InteractableActor);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PullEvent();

	void PullEndEvent();

private:
	bool IsPulled();
};
