// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_A_Door.h"

// Sets default values
ACPP_A_Door::ACPP_A_Door()
	:Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Component"));
	RootComponent = DoorMesh;
	DoorMesh->SetRenderCustomDepth(false);
	DoorMesh->SetCustomDepthStencilValue(1);
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

void ACPP_A_Door::Focus()
{
	DoorMesh->SetRenderCustomDepth(true);
	UE_LOG(LogTemp, Warning, TEXT("Focus"));
}

void ACPP_A_Door::UnFocus()
{
	DoorMesh->SetRenderCustomDepth(false);
	
}

void ACPP_A_Door::Interact(AActor* InteractActor)
{
	if (!bIsOpen)
	{
		Open(InteractActor);
	}
	else
	{
		Close();
	}
}
