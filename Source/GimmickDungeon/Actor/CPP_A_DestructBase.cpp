// Fill out your copyright notice in the Description page of Project Settings.


#include "Field/FieldSystemActor.h"
#include "CPP_A_DestructBase.h"

// Sets default values
ACPP_A_DestructBase::ACPP_A_DestructBase()
	:Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACPP_A_DestructBase::BeginPlay()
{
	Super::BeginPlay();
	bDoOnce = true;
}

// Called every frame
void ACPP_A_DestructBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DebrisSmaller(DeltaTime);
}

void ACPP_A_DestructBase::DebrisSmaller(float DeltaTime)
{
	if (!bDestructed) { return; }

	if (SmallStartElapsedTime != SmallStartTimer)
	{
		SmallStartElapsedTime += DeltaTime;
		SmallStartElapsedTime = FMath::Min(SmallStartElapsedTime, SmallStartTimer);
		return;
	}

	SmallElapsedTime += DeltaTime;
	SmallElapsedTime = FMath::Min(SmallElapsedTime, 1.f);
	float Scale = FMath::Lerp(1.f, 0.f, SmallElapsedTime);
	SetActorScale3D(FVector(Scale));
	if (Scale == 0)
	{
		GetWorld()->DestroyActor(this);
	}
}

bool ACPP_A_DestructBase::Interact(AActor* InteractActor)
{
	if (!Super::Interact(InteractActor)) { return false; }
	if (bDestructed) { return false; }

	GetWorld()->SpawnActor<AActor>(FieldSystem, GetActorLocation(), FRotator::ZeroRotator);

	UActorComponent* Mesh = GetComponentByClass(UPrimitiveComponent::StaticClass());
	if (UPrimitiveComponent* PrimitiveMesh = Cast<UPrimitiveComponent>(Mesh))
	{
		PrimitiveMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	if (ItemBase != nullptr)
	{
		GetWorld()->SpawnActor<AActor>(ItemBase, GetActorLocation(), FRotator::ZeroRotator);
	}
	
	bDestructed = true;


	return true;
}

