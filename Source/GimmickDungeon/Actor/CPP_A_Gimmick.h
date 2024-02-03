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
	/// このアクタのStaticMeshを保持し、フォーカスに使用
	/// BeginPlayにて配列に格納する
	/// </summary>
	// UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UPrimitiveComponent*> MeshList;

protected:
	/// <summary>
	/// 作用可能かどうかを表す
	/// default値は真
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gimmick|State")
	bool bCanInteract = true;

	/// <summary>
	/// ギミックからのアクセスのみを許可するかどうかを表す
	/// 真の場合、ギミックからのみアクセス可能
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gimmick|State")
	bool bGimmickAccessOnly = false;

	/// <summary>
	/// インタラクトが一度切りかどうかを表す
	/// 真の場合、一度切り実行可能
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
	/// Blueprintで使用するイベントディスパッチャー
	/// ギミック間を接続し、連携させる。
	/// </summary>
	/// <param name=""></param>
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJointGimmick);
	UPROPERTY(BlueprintCallable, BlueprintReadOnly, BlueprintAssignable)
	FJointGimmick OnJointGimmick;
};
