// Fill out your copyright notice in the Description page of Project Settings.


#include "BacteriaBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ABacteriaBase::ABacteriaBase()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    MeshComponent->SetCollisionObjectType(ECC_GameTraceChannel1); // "Bacteria" 채널
    MeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore); // 서로 무시

    // 초기 체력
    Health = 100.0f;
}

void ABacteriaBase::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        CameraComp = PlayerPawn->FindComponentByClass<UCameraComponent>();
    }
    Wait = FMath::FRandRange(0.f, WaitTime);
}

void ABacteriaBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CameraComp) {
        PlayerLocation = CameraComp->GetComponentLocation();
    }
}

float ABacteriaBase::TakeDamage(float DamageAmount)
{
    float RemainingDamage = DamageAmount;

    if (Shield > 0.f)
    {
        float Absorbed = FMath::Min(Shield, DamageAmount);
        Shield -= Absorbed;
        RemainingDamage -= Absorbed;

        UE_LOG(LogTemp, Log, TEXT("[Bacteria] 보호막으로 %f 피해 흡수, 남은 보호막: %f"), Absorbed, Shield);
    }

    if (RemainingDamage > 0.f)
    {
        Health -= RemainingDamage;
        if (Health <= 0.f)
        {
            Destroy();
        }
    }

    return DamageAmount;
}