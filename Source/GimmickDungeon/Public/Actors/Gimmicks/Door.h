// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GimmickBase.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API ADoor : public AGimmickBase
{
	GENERATED_BODY()
	
public:
	ADoor();
	virtual void Tick(float DeltaTime) override;

	void Interact(AActor* InteractableActor) override;

	FORCEINLINE bool GetIsOpen() { return bIsOpen; }


protected:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(EditAnywhere,  Category = "Door | Component")
	UStaticMeshComponent* DoorMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Door | State")
	bool bIsOpen = false;

	UPROPERTY(VisibleAnywhere, Category = "Door | State")
	bool bIsLocked = false;

	UPROPERTY(VisibleAnywhere, Category = "Door | State")
	bool bIsMove = false;

	UPROPERTY(VisibleAnywhere, Category = "Door | State")
	FRotator StartRotation;

	UPROPERTY(VisibleAnywhere, Category = "Door | State")
	float CurrentOpenDir = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Door | State")
	float RotateScale = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Door | State")
	float DoorMoveTime = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "Door | State")
	float DoorMoveElapsedSeconds;

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void BeginPlay() override;

	void Open(float Dir);
	void Close();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OpenEvent();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CloseEvent();
	UFUNCTION(BlueprintCallable)
	void Lock();
	UFUNCTION(BlueprintCallable)
	void UnLock();
	UFUNCTION(BlueprintCallable, Blueprintpure)
	bool IsLocked();
	// äJÇ≠ï˚å¸éZèo`
	float GetMoveDirection(FVector InteractActorDir);
};
