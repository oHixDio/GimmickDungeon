// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterfaces/InteractGuideWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractInterface.h"

void UInteractGuideWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// �C�x���g�Ɋ֐����o�C���h
	InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UInteractGuideWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentInteractionDuration = 0.0f;
}

void UInteractGuideWidget::UpdateWidget(const FInteractData* InteractData) const
{
	switch (InteractData->InteractType)
	{
	case EInteractType::Pickup:
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);

		// 0�ȉ��̐��ʂ��ݒ肳��Ă��邱�Ƃ͌��܂��Ȃ����A�������̂悤�Ȑݒ肪����Ă����ꍇ�A�Ή��ł���悤2�����Ƃ�������ɂ��Ă��܂��B
		// 1��1�ȊO�̕\������
		if (InteractData->Quantity < 2)
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			// NSLOCTEXT ���[�J���C�Y���ꂽ�e�L�X�g��񋟂��Ă����
			// Format java�̂悤�ȏ�������format�����쐬�ł���
			QuantityText->SetText(FText::Format(NSLOCTEXT("UInteractGuideWidget", "QuantityText", "x{0}"), InteractData->Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}

		break;
	case EInteractType::Gimmick:
		InteractionProgressBar->SetVisibility(ESlateVisibility::Visible);
		QuantityText->SetVisibility(ESlateVisibility::Collapsed);

		break;
	case EInteractType::NonPlayerCharacter:
		break;
	default:;
	}

	NameText->SetText(InteractData->Name);
}

float UInteractGuideWidget::UpdateInteractionProgress()
{
	return 0.0f;
}