// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GimmicksPlayer.h"
#include "UserInterfaces/InteractGuideWidget.h"
#include "UserInterfaces/PlayerHUD.h"

APlayerHUD::APlayerHUD()
{
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	/*
	if (PlayerScreenClass)
	{
		PlayerScreenWidget = CreateWidget<UCPP_UW_PlayerScreen>(GetWorld(), PlayerScreenClass);
		PlayerScreenWidget->AddToViewport(5);
		PlayerScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	*/
	if (InteractGuideClass)
	{
		InteractGuideWidget = CreateWidget<UInteractGuideWidget>(GetWorld(), InteractGuideClass);
		InteractGuideWidget->AddToViewport(-1);
		InteractGuideWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerHUD::DisplayPlayerScreen()
{
	/*
	if (PlayerScreenWidget)
	{
		PlayerScreenWidget->SetVisibility(ESlateVisibility::Visible);
		bIsPlayerScreenVisible = true;
	}
	*/
}

void APlayerHUD::HidePlayerScreen()
{
	/*
	if (PlayerScreenWidget)
	{
		PlayerScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
		bIsPlayerScreenVisible = false;
	}
	*/
}

void APlayerHUD::ShowInteractGuide() const
{
	if (InteractGuideWidget)
	{
		InteractGuideWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerHUD::HideInteractGuide() const
{
	if (InteractGuideWidget)
	{
		InteractGuideWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerHUD::UpdateInteractGuide(const FInteractData* InteractData) const
{
	if (InteractGuideWidget)
	{
		if (InteractGuideWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractGuideWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractGuideWidget->UpdateWidget(InteractData);
	}
}