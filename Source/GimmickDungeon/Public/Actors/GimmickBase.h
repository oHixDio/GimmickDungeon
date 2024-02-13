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

	FGimmickData() :
		bCanInteract(false),
		bDoOnce(false),
		bGimmickAccessOnly(false),
		InteractDuration(0.0f),
		JointRange(0.0f)
	{};

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


	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	AGimmickBase();
	virtual void Tick(float DeltaTime) override;
protected:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	
	UPROPERTY(EditAnywhere, Category = "Gimmick | Component")
	class UItemComponent* ItemComp;

	UPROPERTY(EditAnywhere, Category = "Gimmick | Component")
	class UWidgetComponent* InteractableWidgetComp;

	UPROPERTY(VisibleAnywhere, Category = "Gimmick | Component")
	TArray<UPrimitiveComponent*> MeshList;

	UPROPERTY(EditAnywhere, Category = "Gimmick | Data")
	FGimmickData GimmickData;

	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void BeginPlay() override;

	void UpdataInteractData();

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void Interact(AActor* InteractableActor)override;
	virtual void EndInteract() override;
};
