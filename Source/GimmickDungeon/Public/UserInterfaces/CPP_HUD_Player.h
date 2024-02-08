// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CPP_HUD_Player.generated.h"


class UCPP_UW_PlayerScreen;
class UCPP_UW_InteractGuide;
/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API ACPP_HUD_Player : public AHUD
{
	GENERATED_BODY()

public:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(EditDefaultsOnly, Category = "Character | Widgets")
	TSubclassOf<UCPP_UW_PlayerScreen> PlayerScreenClass;

	UPROPERTY(EditDefaultsOnly, Category = "Character | Widgets")
	TSubclassOf<UCPP_UW_InteractGuide> InteractGuideClass;

	bool bIsPlayerScreenVisible;
	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	ACPP_HUD_Player();

	void DisplayPlayerScreen();
	void HidePlayerScreen();

	void ShowInteractGuide();
	void HideInteractGuide();
	void UpdateInteractGuide(const struct FInteractableData& InteractableData);

protected:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY()
	UCPP_UW_PlayerScreen* PlayerScreenWidget;

	UPROPERTY()
	UCPP_UW_InteractGuide* InteractGuideWidget;
	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void BeginPlay() override;
};
