// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InteractInterface.h"

// Add default functionality here for any IInteractInterface functions that are not pure virtual.

void IInteractInterface::BeginFocus()
{
}

void IInteractInterface::EndFocus()
{
}

void IInteractInterface::BeginInteract()
{
}

void IInteractInterface::Interact(AActor* InteractableActor)
{
}

void IInteractInterface::EndInteract()
{
}

EInteractType IInteractInterface::GetItemType(AActor* AActor) const
{
    return InteractData.InteractType;
}
