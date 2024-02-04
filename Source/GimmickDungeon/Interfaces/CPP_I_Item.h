// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_I_Item.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_I_Item : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GIMMICKDUNGEON_API ICPP_I_Item
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// �A�N�^��Ԃ�
	virtual AActor* Found() { return nullptr; }
	// �A�N�^��Ԃ�
	virtual AActor* Lost() { return nullptr; }
	// ItemData��Ԃ�
	virtual FName Pickup() { return FName(); }

};
