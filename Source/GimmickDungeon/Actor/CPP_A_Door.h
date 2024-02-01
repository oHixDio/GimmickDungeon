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
	/// ���g���J���Ă���ꍇ�͐^
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Door|State")
	bool bIsOpen = false;

	/// <summary>
	/// �����������Ă���ꍇ�͐^
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
	/// Open�����s�����A�N�^���h�A��Y�������
	/// �v���X�}�C�i�X���Z�o���A�h�A���J�����������߂ĕԂ��B
	/// </summary>
	/// <returns>�h�A���J�������̃X�J���[�l</returns>
	UFUNCTION(BlueprintCallable, Blueprintpure)
	float GetOpenDir(FVector InteractActorDir);

};
