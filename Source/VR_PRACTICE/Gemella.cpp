// Fill out your copyright notice in the Description page of Project Settings.


#include "Gemella.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "StageManager.h"

AGemella::AGemella() {
    PrimaryActorTick.bCanEverTick = true;

    Health = 150.0f;
    MaxSpeed = 300.0f;
    MoveSpeed = 0.f;
    AttackRange = 1500.f;
}

void AGemella::BeginPlay()
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
    // 일정 시간마다 보호막 부여 함수 실행
    GetWorld()->GetTimerManager().SetTimer(
        ShieldGrantTimer,
        this,
        &AGemella::GrantShieldsToNearbyBacteria,
        ShieldGrantInterval,
        true // 반복 호출
    );
}

void AGemella::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!PlayerPawn || !CameraComp) return;
    if (MaxSpeed > MoveSpeed) MoveSpeed += IncSpeed;

    FVector ToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
    Distance = FVector::Dist(GetActorLocation(), CameraComp->GetComponentLocation());
    if (Distance > AttackRange)
    {
        CurrentState = EGemellaState::Approaching;
    }
    else {
        CurrentState = EGemellaState::Wander;
    }

    switch (CurrentState)
    {
    case EGemellaState::Approaching:
        MoveToward(CameraComp->GetComponentLocation(), DeltaTime);
        break;

    case EGemellaState::Wander:
        HandleAttackState(DeltaTime);
        break;
    }
}

void AGemella::GrantShieldsToNearbyBacteria()
{
    TArray<AActor*> BacteriaList;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABacteriaBase::StaticClass(), BacteriaList);

    for (AActor* Actor : BacteriaList)
    {
        ABacteriaBase* Bacteria = Cast<ABacteriaBase>(Actor);
        if (!Bacteria || Bacteria == this) continue;

        float DistanceToBacteria = FVector::Dist(Bacteria->GetActorLocation(), GetActorLocation());

        if (Bacteria->Shield <= 0.f) // 보호막이 없을 때만 부여
        {
            Bacteria->Shield = Bacteria->MaxShield;
            UE_LOG(LogTemp, Log, TEXT("[Gemella] %s에게 보호막 부여"), *Bacteria->GetName());
        }
    }
}

void AGemella::MoveToward(FVector TargetLocation, float DeltaTime)
{
    if (!CameraComp) return;

    // 1. 플레이어 방향 벡터
    FVector ToPlayer = TargetLocation - GetActorLocation();

    // 2. 정수리 방향이 타겟을 향하도록 회전 계산
    FRotator TargetRot = FRotationMatrix::MakeFromZ(ToPlayer).Rotator();

    // 3. 부드럽게 회전
    FRotator SmoothRot = FMath::RInterpTo(GetActorRotation(), TargetRot, DeltaTime, TrackingSpeed);
    SetActorRotation(SmoothRot);

    FVector Movement = GetActorUpVector() * MoveSpeed * DeltaTime;
    AddActorWorldOffset(Movement, true);
}

void AGemella::HandleAttackState(float DeltaTime)
{
    // 랜덤 목표 위치에 천천히 이동
    if ((GetActorLocation() - RandomMoveTarget).Size() < 50.f || FMath::FRand() < 0.01f)
    {
        FVector RandOffset = UKismetMathLibrary::RandomUnitVector() * 600.f;
        RandomMoveTarget = GetActorLocation() + RandOffset;
    }

    MoveToward(RandomMoveTarget, DeltaTime);
}