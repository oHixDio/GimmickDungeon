// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_I_Gimmick.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_I_Gimmick : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class GIMMICKDUNGEON_API ICPP_I_Gimmick
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Focus() {}

	virtual void UnFocus() {}

	virtual bool Interact(AActor* InteractActor) { return true; }
};
