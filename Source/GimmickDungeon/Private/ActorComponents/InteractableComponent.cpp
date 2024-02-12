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

	// �ŏI�`�F�b�N�������猻�݂̎����܂ł̌o�ߎ��� > �`�F�b�N�p�x
	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

void UInteractableComponent::PerformInteractionCheck()
{
	// �ŏI�`�F�b�N�������擾
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	// Trace�����Z�o
	FVector LineTraceStart{ Owner->GetPawnViewLocation() };
	FVector LineTraceEnd{ LineTraceStart + (Owner->GetViewRotation().Vector() * InteractionCheckDistance) };

	// ���ʕ������ǂ���
	float LookDirection = FVector::DotProduct(Owner->GetActorForwardVector(), Owner->GetViewRotation().Vector());

	// ���ʕ����Ȃ��
	if (LookDirection > 0)
	{
		// �⏕���\��
		DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Red, false, 1.0f, 2.0f);

		// Trace�ɕK�v�ȃf�[�^�쐬
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Owner);
		FHitResult HitResult;

		// Trace��Hit�����Ȃ��
		if (GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_Visibility, QueryParams))
		{
			AActor* HitActor = HitResult.GetActor();

			// Hit����Actor��InteractInterface����������Ă���Ȃ��
			if (HitActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
			{
				// �O�񌟏o�����A�N�^�ƈႤ�A�N�^�Ȃ��
				if (HitActor != InteractionData.CurrentInteractableActor)
				{
					FoundInteractable(HitActor);
					return;
				}

				// �O�񌟏o�����A�N�^�Ɠ����A�N�^�Ȃ��
				if (HitActor == InteractionData.CurrentInteractableActor)
				{
					return;
				}
			}
		}
	}

	// �������o�ł��Ȃ�����
	NoInteractableFound();
}

void UInteractableComponent::FoundInteractable(AActor* NewInteractableActor)
{
	// �^�C�}�[�����s���Ȃ��
	if (IsInteracting())
	{
		EndInteract();
	}

	// ���ݕێ����Ă���C���^���N�g�A�N�^������Ȃ��
	if (InteractionData.CurrentInteractableActor)
	{
		TargetInteractableActor = InteractionData.CurrentInteractableActor;
		TargetInteractableActor->EndFocus();
	}

	// �V�������o�����A�N�^��ێ�
	InteractionData.CurrentInteractableActor = NewInteractableActor;
	TargetInteractableActor = NewInteractableActor;

	// HUD�\��
	HUD->UpdateInteractGuide(&TargetInteractableActor->InteractData);

	TargetInteractableActor->BeginFocus();
}

void UInteractableComponent::NoInteractableFound()
{
	// �^�C�}�[���쓮���Ă���Ȃ�Β�~
	if (IsInteracting())
	{
		GetWorld()->GetTimerManager().ClearTimer(InteractionTimerHandle);
	}

	// ���ݕێ����Ă���C���^���N�g�A�N�^������Ȃ��
	if (InteractionData.CurrentInteractableActor)
	{
		// �^�[�Q�b�g���L���Ȃ��
		if (IsValid(TargetInteractableActor.GetObject()))
		{
			TargetInteractableActor->EndFocus();
		}

		HUD->HideInteractGuide();

		// �ێ��A�N�^��j��
		InteractionData.CurrentInteractableActor = nullptr;
		TargetInteractableActor = nullptr;
	}
}


void UInteractableComponent::Interact()
{
	GetWorld()->GetTimerManager().ClearTimer(InteractionTimerHandle);

	// �^�[�Q�b�g���L���Ȃ��
	if (IsValid(TargetInteractableActor.GetObject()))
	{
		TargetInteractableActor->Interact(Owner);
	}
}

void UInteractableComponent::BeginInteract()
{
	// �t�F�C���Z�[�t
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractableActor)
	{
		// �^�[�Q�b�g���L���Ȃ��
		if (IsValid(TargetInteractableActor.GetObject()))
		{
			TargetInteractableActor->BeginInteract();

			// �^�[�Q�b�g�̃C���^���N�g�Ԋu���قڂO�Ȃ瑦���ɃC���^���N�g
			if (FMath::IsNearlyZero(TargetInteractableActor->InteractData.InteractableDuration, 0.1f))
			{
				Interact();
			}
			// �^�[�Q�b�g�̃C���^���N�g�Ԋu���x�点�Ă���C���^���N�g
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

	// �^�[�Q�b�g���L���Ȃ��
	if (IsValid(TargetInteractableActor.GetObject()))
	{
		TargetInteractableActor->EndInteract();
	}
}

