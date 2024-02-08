// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterfaces/CPP_HUD_Player.h"
#include "UserInterfaces/CPP_UW_PlayerScreen.h"
#include "UserInterfaces/Interact/CPP_UW_InteractGuide.h"

ACPP_HUD_Player::ACPP_HUD_Player()
{
}

void ACPP_HUD_Player::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerScreenClass)
	{
		PlayerScreenWidget = CreateWidget<UCPP_UW_PlayerScreen>(GetWorld(), PlayerScreenClass);
		PlayerScreenWidget->AddToViewport(5);
		PlayerScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractGuideClass)
	{
		InteractGuideWidget = CreateWidget<UCPP_UW_InteractGuide>(GetWorld(), InteractGuideClass);
		InteractGuideWidget->AddToViewport(-1);
		InteractGuideWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ACPP_HUD_Player::DisplayPlayerScreen()
{
	if (PlayerScreenWidget)
	{
		PlayerScreenWidget->SetVisibility(ESlateVisibility::Visible);
		bIsPlayerScreenVisible = true;
	}
}

void ACPP_HUD_Player::HidePlayerScreen()
{
	if (PlayerScreenWidget)
	{
		PlayerScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
		bIsPlayerScreenVisible = false;
	}
}

void ACPP_HUD_Player::ShowInteractGuide()
{
	if (InteractGuideWidget)
	{
		InteractGuideWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ACPP_HUD_Player::HideInteractGuide()
{
	if (InteractGuideWidget)
	{
		InteractGuideWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ACPP_HUD_Player::UpdateInteractGuide(const FInteractableData& InteractableData)
{
	if (InteractGuideWidget)
	{
		if (InteractGuideWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractGuideWidget->SetVisibility(ESlateVisibility::Visible);
		}

		// InteractGuideWidget->UpdateWidget(InteractableData);
	}
}


