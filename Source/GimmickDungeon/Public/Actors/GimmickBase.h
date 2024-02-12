// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "GimmickBase.generated.h"

USTRUCT()
struct FGimmickData
{
	GENERATED_USTRUCT_BODY()

	FGimmickData() :bCanInteract(false), bDoOnce(false), bGimmickAccessOnly(false) {};

	UPROPERTY(EditAnywhere)
	bool bCanInteract;

	UPROPERTY(EditAnywhere)
	bool bDoOnce;

	UPROPERTY(EditAnywhere)
	bool bGimmickAccessOnly;

	UPROPERTY(EditAnywhere)
	float InteractDuration;

	UPROPERTY(EditAnywhere)
	float JointRange;
};

UCLASS()
class GIMMICKDUNGEON_API AGimmickBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(EditAnywhere)
	class UItemComponent* ItemComp;

	UPROPERTY(VisibleAnywhere)
	TArray<UPrimitiveComponent*> MeshList;

	UPROPERTY(EditAnywhere)
	FGimmickData GimmickData;

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	AGimmickBase();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	void UpdataInteractData();

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void Interact(AActor* InteractableActor)override;
	virtual void EndInteract() override;
};
