// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_A_Gimmick.h"
#include "CPP_A_DestructBase.generated.h"

UCLASS()
class GIMMICKDUNGEON_API ACPP_A_DestructBase : public ACPP_A_Gimmick
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> FieldSystem;
	

private:
	bool bDestructed = false;
	float SmallStartTimer = 0.5f;
	float SmallStartElapsedTime = 0.f;
	float SmallElapsedTime = 0.f;

public:	
	// Sets default values for this actor's properties
	ACPP_A_DestructBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void DebrisSmaller(float DeltaTime);

public:
	bool Interact(AActor* InteractActor) override;

};
