// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_A_Door.generated.h"

UCLASS()
class GIMMICKDUNGEON_API ACPP_A_Door : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Door|Components")
	UStaticMeshComponent* DoorMesh = nullptr;
	
protected:
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

public:
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
	/// Openを実行したアクタがドアのY軸を基準に
	/// プラスマイナスを算出し、ドアが開く方向を決めて返す。
	/// </summary>
	/// <returns>ドアが開く方向のスカラー値</returns>
	UFUNCTION(BlueprintCallable, Blueprintpure)
	float GetOpenDir(FVector InteractActorDir);

};
