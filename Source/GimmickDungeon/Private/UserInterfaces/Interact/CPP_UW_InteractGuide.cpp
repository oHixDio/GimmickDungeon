// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterfaces/Interact/CPP_UW_InteractGuide.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/CPP_I_Interact.h"

void UCPP_UW_InteractGuide::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// イベントに関数をバインド
	InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UCPP_UW_InteractGuide::NativeConstruct()
{
	Super::NativeConstruct();

	ActionText->SetText(FText::FromString("Press"));
	CurrentInteractionDuration = 0.0f;
}

void UCPP_UW_InteractGuide::UpdateWidget(const FInteractableData* InteractableData) const
{
	switch (InteractableData->InteractableType)
	{
	case EInteractableType::Pickup:
		ActionText->SetText(FText::FromString("Press"));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);

		// 0個以下の数量が設定されていることは決まり上ないが、もしそのような設定がされていた場合、対応できるよう2個未満という判定にしています。
		// 1個と1個以外の表示分け
		if (InteractableData->Quantity < 2)
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			// NSLOCTEXT ローカライズされたテキストを提供してくれる
			// Format javaのような書き方でformat文を作成できる
			QuantityText->SetText(FText::Format(NSLOCTEXT("CPP_UW_InteractGuide", "QuantityText","x{0}"),InteractableData->Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}

		break;
	case EInteractableType::Gimmick:
		break;
	case EInteractableType::NonPlayerCharacter:
		break;
	default: ;
	}
	ActionText->SetText(InteractableData->Action);
	NameText->SetText(InteractableData->Name);
}

float UCPP_UW_InteractGuide::UpdateInteractionProgress()
{
	return 0.0f;
}


