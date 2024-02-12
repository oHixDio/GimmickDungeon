// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gimmicks/Door.h"
#include "Kismet/KismetMathLibrary.h"

ADoor::ADoor()
{
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Root Component");
	SetRootComponent(DoorMesh);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	// init
	bIsOpen = false;
	bIsLocked = false;
	bIsMove = false;
	DoorMoveElapsedSeconds = 0.0f;
	// 0以下なら1にする
	DoorMoveTime = DoorMoveTime < 0 ? 1.0f : DoorMoveTime;
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMove)
	{
		DoorMoveElapsedSeconds += DeltaTime;
		DoorMoveElapsedSeconds = FMath::Min(DoorMoveElapsedSeconds, DoorMoveTime);

		// このフレームで向くべき方向(開き具合)を算出
		float CurrentRotateValue = FMath::Lerp(0, RotateScale * CurrentOpenDir, DoorMoveElapsedSeconds / DoorMoveTime);
		FRotator FrameRotationValue = FRotator(0, CurrentRotateValue, 0);
		FRotator CurrentRotation = UKismetMathLibrary::ComposeRotators(StartRotation, FrameRotationValue);

		SetActorRotation(CurrentRotation);

		// 時間になったら停止
		if (DoorMoveElapsedSeconds == DoorMoveTime)
		{
			bIsMove = false;
			DoorMoveElapsedSeconds = 0.0f;
		}
	}
}

void ADoor::Interact(AActor* InteractableActor)
{
	if (bIsMove) { return; }
	if (bIsOpen)
	{
		Close();
	}
	else
	{
		Open(GetMoveDirection(InteractableActor->GetActorLocation()));
	}
}

void ADoor::Open(float Dir)
{
	bIsOpen = true;
	OpenEvent();

	StartRotation = GetActorRotation();
	CurrentOpenDir = Dir;

	bIsMove = true;
}

void ADoor::Close()
{
	bIsOpen = false;
	CloseEvent();

	StartRotation = GetActorRotation();
	CurrentOpenDir = -CurrentOpenDir;

	bIsMove = true;
}

void ADoor::Lock()
{
}

void ADoor::UnLock()
{
}

bool ADoor::IsLocked()
{
	return false;
}

float ADoor::GetMoveDirection(FVector InteractActorDir)
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
