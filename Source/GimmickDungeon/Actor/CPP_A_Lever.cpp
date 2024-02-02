// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_A_Lever.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ACPP_A_Lever::ACPP_A_Lever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeverFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Mesh"));
	RootComponent = LeverFrameMesh;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	LeverMesh->SetupAttachment(RootComponent);
	LeverMesh->SetRenderCustomDepth(false);
	LeverMesh->SetCustomDepthStencilValue(1);
}

// Called when the game starts or when spawned
void ACPP_A_Lever::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACPP_A_Lever::Tick(float DeltaTime)
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
		RotateValue = UKismetMathLibrary::ComposeRotators(CurRotate,RotateValue);
		LeverMesh->SetRelativeRotation(RotateValue);

		// �^�C�}�[�I������
		if (PullMoveElapsedTimer == PullMoveTimer)
		{
			bSholudCountPullMoveTimer = false;
			PullMoveElapsedTimer = 0.f;
		}
	}

}

void ACPP_A_Lever::Pull(AActor* InteractActor)
{
	if (bSholudCountPullMoveTimer) { return; }
	// Pull�Ŏg�p����ϐ����X�V
	bIsPulled = !bIsPulled;
	CurRotate = LeverMesh->GetRelativeRotation();
	bSholudCountPullMoveTimer = true;
	PullEvent();
}

bool ACPP_A_Lever::IsPulled()
{
	return false;
}

void ACPP_A_Lever::Focus()
{
	LeverMesh->SetRenderCustomDepth(true);
}

void ACPP_A_Lever::UnFocus()
{
	LeverMesh->SetRenderCustomDepth(false);
}

void ACPP_A_Lever::Interact(AActor* InteractActor)
{
	Pull(InteractActor);
}

