// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "./../Interfaces/CPP_I_Gimmick.h"
#include "./../Interfaces/CPP_I_Item.h"
#include "CPP_C_Player.h"

ACPP_C_Player::ACPP_C_Player()
	:Super()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACPP_C_Player::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACPP_C_Player::OnOverlapEnd);
}

void ACPP_C_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Execution
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACPP_C_Player::Interact);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACPP_C_Player::Pickup);
	}
}

void ACPP_C_Player::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_C_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FocusChecker();
}

float ACPP_C_Player::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	// DamageToApply = FMath::Min(Health, DamageToApply);
	// Health -= DamageToApply;
	// UE_LOG(LogTemp, Warning, TEXT("Health %f"), Health);
	return DamageToApply;
}

void ACPP_C_Player::FocusChecker()
{
	// 画面中央の座標取得
	FVector Start;
	FRotator Rotation;
	GetController()->GetPlayerViewPoint(Start, Rotation);
	Start = Start + Rotation.Vector() * CameraBoom->TargetArmLength;
	FVector End = Start + Rotation.Vector() * FocusRange;

	// 画面中央にあるアクタを検出
	FHitResult HitResult;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(5.f);
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult,Start,End,FQuat::Identity, ECC_Visibility, Sphere, Param);

	// Hitしない場合
	if (!HasHit) 
	{
		// アウトライン非表示
		if (LastFocusActor != nullptr)
		{
			if (ICPP_I_Gimmick* GimmickActor = Cast<ICPP_I_Gimmick>(LastFocusActor))
			{
				GimmickActor->UnFocus();
			}
			bFocusGimmick = false;
		}
		LastFocusActor = nullptr;
		return; 
	}

	// Hitしたのが前回と同じアクタの場合
	if (HitResult.GetActor() == LastFocusActor) { return; }

	// ↓↓ 新しく検出したアクタ ↓↓ //

	// アウトライン非表示
	if (LastFocusActor != nullptr)
	{
		if (ICPP_I_Gimmick* GimmickActor = Cast<ICPP_I_Gimmick>(LastFocusActor))
		{
			GimmickActor->UnFocus();
		}
		bFocusGimmick = false;
	}

	// Hitしたアクタを保持
	LastFocusActor = HitResult.GetActor();
	
	// アウトライン表示
	if (ICPP_I_Gimmick* GimmickActor = Cast<ICPP_I_Gimmick>(LastFocusActor))
	{
		GimmickActor->Focus();
		bFocusGimmick = true;
	}
}

void ACPP_C_Player::Interact(const FInputActionValue& Value)
{
	if (ICPP_I_Gimmick* GimmickActor = Cast<ICPP_I_Gimmick>(LastFocusActor))
	{
		GimmickActor->Interact(this);
	}
}

void ACPP_C_Player::Pickup(const FInputActionValue& Value)
{
	if (bFocusGimmick) { return; }
	// アイテムが近くにあるのなら取得する
	if (FounndItemActorList.Num() != 0)
	{
		// 最後の要素
		int index = FounndItemActorList.Num()-1;
		if (ICPP_I_Item* Item = Cast<ICPP_I_Item>(FounndItemActorList[index]))
		{
			FName ItemName = Item->Pickup();
			UE_LOG(LogTemp, Log, TEXT("ItemName %s"), *ItemName.ToString());
		}

	}
}

void ACPP_C_Player::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		// Itemなら発見リストに追加
		if (Cast<ICPP_I_Item>(OtherActor))
		{
			FounndItemActorList.Add(OtherActor);
		}
	}
}

void ACPP_C_Player::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr)
	{
		// Itemなら発見リストから削除
		if (Cast<ICPP_I_Item>(OtherActor))
		{
			FounndItemActorList.Remove(OtherActor);
		}
	}
}
