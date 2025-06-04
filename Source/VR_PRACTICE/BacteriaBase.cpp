// Fill out your copyright notice in the Description page of Project Settings.


#include "BacteriaBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "StageManager.h"

ABacteriaBase::ABacteriaBase()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MeshComponent->SetCollisionObjectType(ECC_GameTraceChannel1); // "Bacteria" ä��

    MeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

    MeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore); // ���� ����

    ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
    ShieldMesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ShieldAsset(TEXT("/Game/Niagara/Shield/IcoSphere.IcoSphere")); // ���� ��η�!
    if (ShieldAsset.Succeeded())
    {
        ShieldMesh->SetStaticMesh(ShieldAsset.Object);
    }

    // �ʱ� ü��
    Health = 100.0f;
}

float ABacteriaBase::getHealth()
{
    return Health;
}

void ABacteriaBase::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        CameraComp = PlayerPawn->FindComponentByClass<UCameraComponent>();
    }
    AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
    if (StageManager)
    {
        StageManager->RegisterBacteria(this);
    }
    // ��Ƽ����/������/��ġ/���� �� �߰� ����
    ShieldMesh->SetVisibility(Shield); // ó���� �� ���̰�
    ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // �浹 X
    ShieldMesh->SetWorldScale3D(GetActorScale3D() * 2.f); // ��ü���� ���� ũ��
}

void ABacteriaBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CameraComp) {
        PlayerLocation = CameraComp->GetComponentLocation();
    }
}

void ABacteriaBase::TakeDamageBac()
{
    if (Shield)
    {
        ShieldMesh->SetVisibility(false);
        Shield = false;
    }
    else {
        OnDeath();
        Destroy();
    }
}

void ABacteriaBase::Destroyed()
{
    Super::Destroyed();

    AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
    if (StageManager)
    {
        StageManager->UnregisterBacteria(this);
    }
}