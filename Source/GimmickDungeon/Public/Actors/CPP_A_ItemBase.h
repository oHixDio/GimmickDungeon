// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "./../Interfaces/CPP_I_Item.h"
#include "CPP_A_ItemBase.generated.h"

UCLASS(Blueprintable)
class GIMMICKDUNGEON_API ACPP_A_ItemBase : public AActor, public ICPP_I_Item
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* PlayerDetectComp;

	UPROPERTY(EditAnywhere)
	float DetectRadius = 200.f;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* ItemNiagaraSystem;

	UPROPERTY(EditAnywhere)
	FName Name = "Item";

public:	
	// Sets default values for this actor's properties
	ACPP_A_ItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	AActor* Found() override;
	AActor* Lost() override;
	FName Pickup() override;
};
