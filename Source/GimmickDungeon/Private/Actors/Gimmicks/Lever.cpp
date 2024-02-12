// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gimmicks/Lever.h"
#include <Kismet/KismetMathLibrary.h>

ALever::ALever()
	:Super()
{
	LeverFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Mesh"));
	RootComponent = LeverFrameMesh;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	LeverMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Pull�̎��s���犮���܂ł̃^�C�}�[
	if (bSholudCountPullMoveTimer)
	{
		PullMoveElapsedTimer += DeltaTime;
		// �w��̒l�Ŋۂ߂�
		PullMoveElapsedTimer = FMath::Min(PullMoveElapsedTimer, PullMoveTimer);

		// �����Pull�ł̓|���������߂�
		float Dir = 1.f;
		if (!bIsPulled) { Dir = -1.f; }

		// ���݂̃t���[���Ō����ׂ��������^�C�}�[��Alpha�Ƃ��āA���`��ԂŎ擾
		float CurrentRotateScale = FMath::Lerp(0, PULL_SCALE * Dir, PullMoveElapsedTimer / PullMoveTimer);
		FRotator RotateValue = FRotator(0, 0, CurrentRotateScale);

		// Pull���s�J�n���̑��Ίp�x�ɑ΂��Ċ|�����킹��
		RotateValue = UKismetMathLibrary::ComposeRotators(CurRotate, RotateValue);
		LeverMesh->SetRelativeRotation(RotateValue);

		// �^�C�}�[�I������
		if (PullMoveElapsedTimer == PullMoveTimer)
		{
			bSholudCountPullMoveTimer = false;
			PullMoveElapsedTimer = 0.f;
			PullEndEvent();
		}
	}

}

void ALever::Pull(AActor* InteractableActor)
{
	if (bSholudCountPullMoveTimer) { return; }
	// Pull�Ŏg�p����ϐ����X�V
	bIsPulled = !bIsPulled;
	CurRotate = LeverMesh->GetRelativeRotation();
	bSholudCountPullMoveTimer = true;
	PullEvent();
}

void ALever::PullEndEvent()
{
	// OnJointGimmick.Broadcast();
}

bool ALever::IsPulled()
{
	return false;
}

void ALever::Interact(AActor* InteractableActor)
{
	Super::Interact(InteractableActor);

	Pull(InteractableActor);
}