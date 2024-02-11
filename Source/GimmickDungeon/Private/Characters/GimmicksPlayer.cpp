// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GimmicksPlayer.h"
#include "ActorComponents/InteractableComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGimmicksPlayer::AGimmicksPlayer()
	:Super()
{
	InteractableComp = CreateDefaultSubobject<UInteractableComponent>("Interactable Component");
}

void AGimmicksPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, InteractableComp, &UInteractableComponent::BeginInteract);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, InteractableComp, &UInteractableComponent::EndInteract);
	}
}

void AGimmicksPlayer::BeginPlay()
{
	Super::BeginPlay();

	// –Úü‚ÆƒJƒƒ‰‚Ì‚‚³‚ð‡‚í‚¹‚é
	BaseEyeHeight = CameraBoom->GetRelativeLocation().Z;
}

void AGimmicksPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AGimmicksPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	// DamageToApply = FMath::Min(Health, DamageToApply);
	// Health -= DamageToApply;
	// UE_LOG(LogTemp, Warning, TEXT("Health %f"), Health);
	return DamageToApply;
}
