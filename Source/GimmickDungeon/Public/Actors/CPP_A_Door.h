// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_A_Gimmick.h"
#include "CPP_A_Door.generated.h"

UCLASS(Blueprintable)
class GIMMICKDUNGEON_API ACPP_A_Door : public ACPP_A_Gimmick
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|Components")
	UStaticMeshComponent* DoorMesh = nullptr;
	
	/// <summary>
	/// 自身が開いている場合は真
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Door|State")
	bool bIsOpen = false;

	/// <summary>
	/// 鍵がかかっている場合は真
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Door|State")
	bool bIsLocked = false;

	/// <summary>
	/// Open開始時の回転を保持する
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|State")
	FRotator CurrentRotate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|State")
	float RotateScale = 90;

public:	
	// Sets default values for this actor's properties
	ACPP_A_Door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE bool GetIsOpen() { return bIsOpen; }

protected:
	UFUNCTION(BlueprintCallable)
	void Open(AActor* InteractActor);
	UFUNCTION(BlueprintCallable)
	void Close();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OpenEvent(float Dir);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CloseEvent();
	UFUNCTION(BlueprintCallable)
	void Lock();
	UFUNCTION(BlueprintCallable)
	void UnLock();
	UFUNCTION(BlueprintCallable, Blueprintpure)
	bool IsLocked();

private:
	/// <summary>
	/// 内積を使用し、Θの正負で扉が開く方向を定め、正負を返す。
	/// </summary>
	/// <returns>ドアが開く方向の正負</returns>
	float GetOpenDir(FVector InteractActorDir);

public:

	UFUNCTION(BlueprintCallable)
	virtual bool Interact(AActor* InteractActor) override;
};
