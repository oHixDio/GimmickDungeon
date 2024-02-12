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
	// 0�ȉ��Ȃ�1�ɂ���
	DoorMoveTime = DoorMoveTime < 0 ? 1.0f : DoorMoveTime;
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMove)
	{
		DoorMoveElapsedSeconds += DeltaTime;
		DoorMoveElapsedSeconds = FMath::Min(DoorMoveElapsedSeconds, DoorMoveTime);

		// ���̃t���[���Ō����ׂ�����(�J���)���Z�o
		float CurrentRotateValue = FMath::Lerp(0, RotateScale * CurrentOpenDir, DoorMoveElapsedSeconds / DoorMoveTime);
		FRotator FrameRotationValue = FRotator(0, CurrentRotateValue, 0);
		FRotator CurrentRotation = UKismetMathLibrary::ComposeRotators(StartRotation, FrameRotationValue);

		SetActorRotation(CurrentRotation);

		// ���ԂɂȂ������~
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
	// ����Y�����ɐL�т�x�N�g��
	FVector V1 = GetActorRightVector();
	// ���̌��_����C���^���N�g�A�N�^�ɐL�т�x�N�g��
	FVector V2 = InteractActorDir - GetActorLocation();
	// ���ς����A�p�x���Z�o
	float Dot = FVector::DotProduct(V1, V2);
	// �p�x���v���X�Ȃ�}�C�i�X�A�}�C�i�X�Ȃ�v���X
	if (Dot > 0)
	{
		return -1;
	}
	return 1;
}
