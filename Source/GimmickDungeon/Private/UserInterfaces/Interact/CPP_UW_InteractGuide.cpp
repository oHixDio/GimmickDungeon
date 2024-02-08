// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterfaces/Interact/CPP_UW_InteractGuide.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/CPP_I_Interact.h"

void UCPP_UW_InteractGuide::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// �C�x���g�Ɋ֐����o�C���h
	InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UCPP_UW_InteractGuide::NativeConstruct()
{
	Super::NativeConstruct();

	ActionVerbText->SetText(FText::FromString("Press"));
	CurrentInteractionDuration = 0.0f;
}

void UCPP_UW_InteractGuide::UpdateWidget(const FInteractableData& InteractableData)
{
	switch (InteractableData.InteractableType)
	{
	case EInteractableType::Pickup:
		ActionVerbText->SetText(FText::FromString("Press"));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);

		// 0�ȉ��̐��ʂ��ݒ肳��Ă��邱�Ƃ͌��܂��Ȃ����A�������̂悤�Ȑݒ肪����Ă����ꍇ�A�Ή��ł���悤2�����Ƃ�������ɂ��Ă��܂��B
		// 1��1�ȊO�̕\������
		if (InteractableData.Quantity < 2)
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			// NSLOCTEXT ���[�J���C�Y���ꂽ�e�L�X�g��񋟂��Ă����
			// Format java�̂悤�ȏ�������format�����쐬�ł���
			QuantityText->SetText(FText::Format(NSLOCTEXT("CPP_UW_InteractGuide", "QuantityText","x{0}"),InteractableData.Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}

		break;
	case EInteractableType::Gimmick:
		break;
	case EInteractableType::NonPlayerCharacter:
		break;
	default:
		break;
	}
}

float UCPP_UW_InteractGuide::UpdateInteractionProgress()
{
	return 0.0f;
}


