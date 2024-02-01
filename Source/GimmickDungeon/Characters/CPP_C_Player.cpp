// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "CPP_C_Player.h"

ACPP_C_Player::ACPP_C_Player()
	:Super()
{
}

void ACPP_C_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Execution
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACPP_C_Player::Interact);
	}
}

void ACPP_C_Player::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_C_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FocusChecker();
}

float ACPP_C_Player::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	// DamageToApply = FMath::Min(Health, DamageToApply);
	// Health -= DamageToApply;
	// UE_LOG(LogTemp, Warning, TEXT("Health %f"), Health);
	return DamageToApply;
}

void ACPP_C_Player::FocusChecker()
{
	// ƒJƒƒ‰‚©‚çRange•ªL‚Ñ‚éÀ•W‚ðŽæ“¾
	FVector Start;
	FRotator Rotation;
	GetController()->GetPlayerViewPoint(Start, Rotation);
	Start = Start + Rotation.Vector() * CameraBoom->TargetArmLength;
	FVector End = Start + Rotation.Vector() * FocusRange;

	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1);

	AActor* HitActor = HitResult.GetActor();

	if (LastFocusActor == HitActor) { return; }

	LastFocusActor = HitActor;

	if (LastFocusActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FocusActor is %s"), *LastFocusActor->GetActorNameOrLabel());
	}
	
	// Focus

	// UnFocus
}

void ACPP_C_Player::Interact(const FInputActionValue& Value)
{
}
