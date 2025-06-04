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
    MeshComponent->SetCollisionObjectType(ECC_GameTraceChannel1); // "Bacteria" 채널

    MeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

    MeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore); // 서로 무시

    ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
    ShieldMesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ShieldAsset(TEXT("/Game/Niagara/Shield/IcoSphere.IcoSphere")); // 실제 경로로!
    if (ShieldAsset.Succeeded())
    {
        ShieldMesh->SetStaticMesh(ShieldAsset.Object);
    }

    // 초기 체력
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
    // 머티리얼/스케일/위치/투명도 등 추가 세팅
    ShieldMesh->SetVisibility(Shield); // 처음엔 안 보이게
    ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 충돌 X
    ShieldMesh->SetWorldScale3D(GetActorScale3D() * 2.f); // 본체보다 조금 크게
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