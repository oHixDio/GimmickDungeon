// Fill out your copyright notice in the Description page of Project Settings.

#include "Interfaces/InteractInterface.h"
#include "ActorComponents/InteractableComponent.h"
#include "UserInterfaces/PlayerHUD.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	InteractionCheckFrequency = 0.1f;
	InteractionCheckDistance = 300.0f;
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<APawn>(GetOwner());
	HUD = GetWorld()->GetFirstPlayerController()->GetHUD<APlayerHUD>();
}

void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 最終チェック時刻から現在の時刻までの経過時間 > チェック頻度
	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

void UInteractableComponent::PerformInteractionCheck()
{
	// 最終チェック時刻を取得
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	// Trace距離算出
	FVector LineTraceStart{ Owner->GetPawnViewLocation() };
	FVector LineTraceEnd{ LineTraceStart + (Owner->GetViewRotation().Vector() * InteractionCheckDistance) };

	// 正面方向かどうか
	float LookDirection = FVector::DotProduct(Owner->GetActorForwardVector(), Owner->GetViewRotation().Vector());

	// 正面方向ならば
	if (LookDirection > 0)
	{
		// 補助線表示
		DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Red, false, 1.0f, 2.0f);

		// Traceに必要なデータ作成
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Owner);
		FHitResult HitResult;

		// TraceがHitしたならば
		if (GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_Visibility, QueryParams))
		{
			AActor* HitActor = HitResult.GetActor();

			// HitしたActorにInteractInterfaceが実装されているならば
			if (HitActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
			{
				// 前回検出したアクタと違うアクタならば
				if (HitActor != InteractionData.CurrentInteractableActor)
				{
					FoundInteractable(HitActor);
					return;
				}

				// 前回検出したアクタと同じアクタならば
				if (HitActor == InteractionData.CurrentInteractableActor)
				{
					return;
				}
			}
		}
	}

	// 何も検出できなかった
	NoInteractableFound();
}

void UInteractableComponent::FoundInteractable(AActor* NewInteractableActor)
{
	// タイマーが実行中ならば
	if (IsInteracting())
	{
		EndInteract();
	}

	// 現在保持しているインタラクトアクタがあるならば
	if (InteractionData.CurrentInteractableActor)
	{
		TargetInteractableActor = InteractionData.CurrentInteractableActor;
		TargetInteractableActor->EndFocus();
	}

	// 新しく検出したアクタを保持
	InteractionData.CurrentInteractableActor = NewInteractableActor;
	TargetInteractableActor = NewInteractableActor;

	// HUD表示
	HUD->UpdateInteractGuide(&TargetInteractableActor->InteractData);

	TargetInteractableActor->BeginFocus();
}

void UInteractableComponent::NoInteractableFound()
{
	// タイマーが作動しているならば停止
	if (IsInteracting())
	{
		GetWorld()->GetTimerManager().ClearTimer(InteractionTimerHandle);
	}

	// 現在保持しているインタラクトアクタがあるならば
	if (InteractionData.CurrentInteractableActor)
	{
		// ターゲットが有効ならば
		if (IsValid(TargetInteractableActor.GetObject()))
		{
			TargetInteractableActor->EndFocus();
		}

		HUD->HideInteractGuide();

		// 保持アクタを破棄
		InteractionData.CurrentInteractableActor = nullptr;
		TargetInteractableActor = nullptr;
	}
}


void UInteractableComponent::Interact()
{
	GetWorld()->GetTimerManager().ClearTimer(InteractionTimerHandle);

	// ターゲットが有効ならば
	if (IsValid(TargetInteractableActor.GetObject()))
	{
		TargetInteractableActor->Interact(Owner);
	}
}

void UInteractableComponent::BeginInteract()
{
	// フェイルセーフ
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractableActor)
	{
		// ターゲットが有効ならば
		if (IsValid(TargetInteractableActor.GetObject()))
		{
			TargetInteractableActor->BeginInteract();

			// ターゲットのインタラクト間隔がほぼ０なら即座にインタラクト
			if (FMath::IsNearlyZero(TargetInteractableActor->InteractData.InteractableDuration, 0.1f))
			{
				Interact();
			}
			// ターゲットのインタラクト間隔分遅らせてからインタラクト
			else
			{
				GetWorld()->GetTimerManager().SetTimer
				(
					InteractionTimerHandle,
					this,
					&UInteractableComponent::Interact,
					TargetInteractableActor->InteractData.InteractableDuration,
					false
				);
			}
		}
	}
}

void UInteractableComponent::EndInteract()
{
	GetWorld()->GetTimerManager().ClearTimer(InteractionTimerHandle);

	// ターゲットが有効ならば
	if (IsValid(TargetInteractableActor.GetObject()))
	{
		TargetInteractableActor->EndInteract();
	}
}

