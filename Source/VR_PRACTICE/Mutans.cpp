// Fill out your copyright notice in the Description page of Project Settings.


#include "Mutans.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AMutans::AMutans() {
    PrimaryActorTick.bCanEverTick = true;

    Health = 500.0f;
    MoveSpeed = 500.f;

    Point = 30;
}

void AMutans::performBehavior(float DeltaTime)
{
    if (!PlayerPawn || !CameraComp) return;

    // 1. 플레이어 방향 벡터
    FVector ToPlayer = CameraComp->GetComponentLocation() - GetActorLocation();

    // 2. 정수리 방향이 타겟을 향하도록 회전 계산
    FRotator TargetRot = FRotationMatrix::MakeFromZ(ToPlayer).Rotator();

    // 3. 부드럽게 회전
    FRotator SmoothRot = FMath::RInterpTo(GetActorRotation(), TargetRot, DeltaTime, TrackingSpeed);
    SetActorRotation(SmoothRot);

    // 4. 항상 현재 정수리 방향으로 이동
    FVector Movement = GetActorUpVector() * MoveSpeed * DeltaTime;
    AddActorWorldOffset(Movement, true);

    // 5. 충돌 판정
    Distance = FVector::Dist(GetActorLocation(), CameraComp->GetComponentLocation());
    if (Distance < AttackRange)
    {
        OnPlayerAttacked.Broadcast(this);
        UGameplayStatics::ApplyDamage(PlayerPawn, AttackPower, nullptr, this, nullptr);
        Destroy();
    }
}