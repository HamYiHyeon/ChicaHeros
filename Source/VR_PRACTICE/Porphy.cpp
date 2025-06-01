// Fill out your copyright notice in the Description page of Project Settings.


#include "Porphy.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

APorphy::APorphy() {
    PrimaryActorTick.bCanEverTick = true;

    Health = 400.0f;
    MaxSpeed = 250.0f;
    MoveSpeed = 0.f;
}

void APorphy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!PlayerPawn || !CameraComp) return;
    if (MaxSpeed > MoveSpeed) MoveSpeed += IncSpeed;

    // 3. 전방위 회전 (X, Y, Z축으로 천천히)
    FRotator SpinRotation = FRotator(SpinSpeedX * DeltaTime, SpinSpeedY * DeltaTime, SpinSpeedZ * DeltaTime);
    AddActorLocalRotation(SpinRotation);

    // 1. 플레이어 방향 벡터
    FVector ToPlayer = CameraComp->GetComponentLocation() - GetActorLocation();
    FVector MoveDirection = ToPlayer.GetSafeNormal();

    // 2. 천천히 플레이어 방향으로 이동
    FVector Movement = MoveDirection * MoveSpeed * DeltaTime;
    AddActorWorldOffset(Movement, true);

    //충돌 판정
    Distance = FVector::Dist(GetActorLocation(), CameraComp->GetComponentLocation());
    if (Distance < AttackRange)
    {
        OnPlayerAttacked.Broadcast();
        UGameplayStatics::ApplyDamage(PlayerPawn, AttackPower, nullptr, this, nullptr);
        Destroy();
    }
}