// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./../Interfaces/CPP_I_Gimmick.h"
#include "GameFramework/Actor.h"
#include "CPP_A_Door.generated.h"

UCLASS()
class GIMMICKDUNGEON_API ACPP_A_Door : public AActor, public ICPP_I_Gimmick
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|Components")
	UStaticMeshComponent* DoorMesh = nullptr;
	
	/// <summary>
	/// ���g���J���Ă���ꍇ�͐^
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Door|State")
	bool bIsOpen = false;

	/// <summary>
	/// �����������Ă���ꍇ�͐^
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Door|State")
	bool bIsLocked = false;

	/// <summary>
	/// Open�J�n���̉�]��ێ�����
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
	/// ���ς��g�p���A���̐����Ŕ����J���������߁A������Ԃ��B
	/// </summary>
	/// <returns>�h�A���J�������̐���</returns>
	float GetOpenDir(FVector InteractActorDir);

public:
	virtual void Focus() override;

	virtual void UnFocus() override;

	virtual void Interact(AActor* InteractActor) override;
};