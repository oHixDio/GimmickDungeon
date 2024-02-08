// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CPP_A_Door.h"

// Sets default values
ACPP_A_Door::ACPP_A_Door()
	:Super()
{
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Component"));
	RootComponent = DoorMesh;
}

// Called when the game starts or when spawned
void ACPP_A_Door::BeginPlay()
{
	Super::BeginPlay();
	CurrentRotate = GetActorRotation();
}

// Called every frame
void ACPP_A_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_A_Door::Open(AActor* InteractActor)
{
	if (InteractActor == nullptr) { return; }
	if (bIsOpen) { return; }
	bIsOpen = true;
	OpenEvent(GetOpenDir(InteractActor->GetActorLocation()));
}

void ACPP_A_Door::Close()
{
	bIsOpen = false;
	CloseEvent();
}

void ACPP_A_Door::Lock()
{
	bIsLocked = true;
}

void ACPP_A_Door::UnLock()
{
	bIsLocked = false;
}

bool ACPP_A_Door::IsLocked()
{
	return bIsLocked;
}

float ACPP_A_Door::GetOpenDir(FVector InteractActorDir)
{
	// 扉のY方向に伸びるベクトル
	FVector V1 = GetActorRightVector();
	// 扉の原点からインタラクトアクタに伸びるベクトル
	FVector V2 = InteractActorDir - GetActorLocation();
	// 内積を取り、角度を算出
	float Dot = FVector::DotProduct(V1, V2);
	// 角度がプラスならマイナス、マイナスならプラス
	if (Dot > 0) 
	{
		return -1;
	}
	return 1;
}

bool ACPP_A_Door::Interact(AActor* InteractActor)
{
	if (!Super::Interact(InteractActor)) { return false; }
	if (!bIsOpen)
	{
		Open(InteractActor);
	}
	else
	{
		Close();
	}
	return true;
}

