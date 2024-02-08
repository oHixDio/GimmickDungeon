// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./../Interfaces/CPP_I_Gimmick.h"
#include "GameFramework/Actor.h"
#include "CPP_A_Gimmick.generated.h"

UCLASS(ABSTRACT)
class GIMMICKDUNGEON_API ACPP_A_Gimmick : public AActor, public ICPP_I_Gimmick
{
	GENERATED_BODY()

private:
	/// <summary>
	/// ���̃A�N�^��StaticMesh��ێ����A�t�H�[�J�X�Ɏg�p
	/// BeginPlay�ɂĔz��Ɋi�[����
	/// </summary>
	// UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UPrimitiveComponent*> MeshList;

protected:
	/// <summary>
	/// ��p�\���ǂ�����\��
	/// default�l�͐^
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gimmick|State")
	bool bCanInteract = true;

	/// <summary>
	/// �M�~�b�N����̃A�N�Z�X�݂̂������邩�ǂ�����\��
	/// �^�̏ꍇ�A�M�~�b�N����̂݃A�N�Z�X�\
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gimmick|State")
	bool bGimmickAccessOnly = false;

	/// <summary>
	/// �C���^���N�g����x�؂肩�ǂ�����\��
	/// �^�̏ꍇ�A��x�؂���s�\
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gimmick|State")
	bool bDoOnce = false;
	
public:	
	// Sets default values for this actor's properties
	ACPP_A_Gimmick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Focus() override;
	virtual void UnFocus() override;
	virtual bool Interact(AActor* InteractActor) override;

	/// <summary>
	/// Blueprint�Ŏg�p����C�x���g�f�B�X�p�b�`���[
	/// �M�~�b�N�Ԃ�ڑ����A�A�g������B
	/// </summary>
	/// <param name=""></param>
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJointGimmick);
	UPROPERTY(BlueprintCallable, BlueprintReadOnly, BlueprintAssignable)
	FJointGimmick OnJointGimmick;
};
