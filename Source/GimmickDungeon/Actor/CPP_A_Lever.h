// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_A_Gimmick.h"
#include "CPP_A_Lever.generated.h"

// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJointGimmick);

UCLASS(Blueprintable)
class GIMMICKDUNGEON_API ACPP_A_Lever : public ACPP_A_Gimmick
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lever|Components")
	UStaticMeshComponent* LeverMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lever|Components")
	UStaticMeshComponent* LeverFrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lever|State")
	bool bIsPulled = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lever|State")
	bool bSholudCountPullMoveTimer = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lever|State")
	float PULL_SCALE = 60.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lever|State")
	FRotator CurRotate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lever|State")
	float PullMoveTimer = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lever|State")
	float PullMoveElapsedTimer = 0.f;
	
public:	
	// Sets default values for this actor's properties
	ACPP_A_Lever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable)
	void Pull(AActor* InteractActor);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PullEvent();

	void PullEndEvent();
	
private:
	bool IsPulled();

public:
	bool Interact(AActor* InteractActor) override;
};
