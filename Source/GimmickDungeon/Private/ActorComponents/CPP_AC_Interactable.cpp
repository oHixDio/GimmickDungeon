// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/CPP_I_Interact.h"
#include "ActorComponents/CPP_AC_Interactable.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UCPP_AC_Interactable::UCPP_AC_Interactable()
{
	// init
	PrimaryComponentTick.bCanEverTick = true;
	InteractionCheckFrequency = 0.1f;
	InteractionCheckDistance = 300.0f;
}

// Called when the game starts
void UCPP_AC_Interactable::BeginPlay()
{
	Super::BeginPlay();

	// OwnerのアクターがPawnではないとき、このコンポーネントを削除する。
	if (!Cast<APawn>(GetOwner()))
	{
		DestroyComponent();
	}
	else
	{
		Owner = Cast<APawn>(GetOwner());
		bShouldInteractionCheck = true;
	}
}

// Called every frame
void UCPP_AC_Interactable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bShouldInteractionCheck) { return; }
	// 最終チェック時刻から現在の時刻までの経過時間 > チェック頻度
	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

void UCPP_AC_Interactable::PerformInteractionCheck()
{
	// 最終チェック時刻を取得
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();
	
	// Trace距離算出
	FVector Start{ Owner->GetPawnViewLocation() };
	FVector End{ Start + (Owner->GetViewRotation().Vector() * InteractionCheckDistance) };

	// 正面方向かどうか
	float LookDirection = FVector::DotProduct(Owner->GetActorForwardVector(), Owner->GetViewRotation().Vector());

	if (LookDirection > 0)
	{
		// 補助線表示
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 2.0f);

		// Traceに必要なデータ作成
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Owner);
		FHitResult HitResult;

		// TraceがHitしたならば
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
		{
			AActor* HitActor = HitResult.GetActor();

			// HitしたActorにInteractInterfaceが実装されているならば
			if (HitActor->GetClass()->ImplementsInterface(UCPP_I_Interact::StaticClass()))
			{
				const float Distance = (Start - HitResult.ImpactPoint).Size();

				if (HitActor != InteractionData.CurrentInteractableActor && Distance <= InteractionCheckDistance)
				{
					FoundInteractable(HitActor);
					return;
				}

				if (HitActor != InteractionData.CurrentInteractableActor)
				{
					return;
				}
			}
		}
	}

	NoInteractableFound();
}

void UCPP_AC_Interactable::FoundInteractable(AActor* newInteractable)
{
}

void UCPP_AC_Interactable::NoInteractableFound()
{
}

void UCPP_AC_Interactable::BeginInteract()
{
}

void UCPP_AC_Interactable::Interact()
{
}

void UCPP_AC_Interactable::EndInteract()
{
}



