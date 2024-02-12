// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterfaces/InteractGuideWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractInterface.h"

void UInteractGuideWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// イベントに関数をバインド
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

		// 0個以下の数量が設定されていることは決まり上ないが、もしそのような設定がされていた場合、対応できるよう2個未満という判定にしています。
		// 1個と1個以外の表示分け
		if (InteractData->Quantity < 2)
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			// NSLOCTEXT ローカライズされたテキストを提供してくれる
			// Format javaのような書き方でformat文を作成できる
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