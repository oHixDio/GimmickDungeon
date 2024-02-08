// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_A_Gimmick.h"
#include "CPP_A_RoomChangeDoor.generated.h"

UCLASS()
class GIMMICKDUNGEON_API ACPP_A_RoomChangeDoor : public ACPP_A_Gimmick
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomChangeDoor|Components")
	UStaticMeshComponent* RoomChangeDoorMesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RoomChangeDoor")
	TSoftObjectPtr<UWorld> LoadLevel;
	
public:	
	// Sets default values for this actor's properties
	ACPP_A_RoomChangeDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool Interact(AActor* InteractActor) override;
};
