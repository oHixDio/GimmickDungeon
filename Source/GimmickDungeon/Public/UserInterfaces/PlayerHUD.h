// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"


class UInteractGuideWidget;
/**
 * 
 */
UCLASS()
class GIMMICKDUNGEON_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY(EditDefaultsOnly, Category = "Character | Widgets")
	TSubclassOf<UInteractGuideWidget> InteractGuideClass;

	bool bIsPlayerScreenVisible;
	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	APlayerHUD();

	void DisplayPlayerScreen();
	void HidePlayerScreen();

	void ShowInteractGuide() const;
	void HideInteractGuide() const;
	void UpdateInteractGuide(const struct FInteractData* InteractData) const;

protected:
	//====================================================================================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================================================================================
	UPROPERTY()
	UInteractGuideWidget* InteractGuideWidget;
	//====================================================================================================================================================================================
	// FUNCTIONS
	//====================================================================================================================================================================================
	virtual void BeginPlay() override;
};
