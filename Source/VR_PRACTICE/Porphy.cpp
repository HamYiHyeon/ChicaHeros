// Fill out your copyright notice in the Description page of Project Settings.


#include "Porphy.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

APorphy::APorphy() {
    PrimaryActorTick.bCanEverTick = true;

    Health = 400.0f;
    MaxSpeed = 250.0f;
    MoveSpeed = 0.f;
    AttackRange = 500.f;

    NiagaraEffect = LoadObject<UNiagaraSystem>(
        nullptr,
        TEXT("/Game/Niagara/NS_LowPolyExplosion.NS_LowPolyExplosion")
    );
}

void APorphy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!PlayerPawn || !CameraComp) return;
    if (MaxSpeed > MoveSpeed) MoveSpeed += IncSpeed;

    // 3. ������ ȸ�� (X, Y, Z������ õõ��)
    FRotator SpinRotation = FRotator(SpinSpeedX * DeltaTime, SpinSpeedY * DeltaTime, SpinSpeedZ * DeltaTime);
    AddActorLocalRotation(SpinRotation);
    
    Distance = FVector::Dist(GetActorLocation(), CameraComp->GetComponentLocation());
    if (Distance < AttackRange) {
        CurrentState = EPorphyState::Burst;
    }
    else {
        CurrentState = EPorphyState::Approaching;
    }

    switch (CurrentState) {
    case EPorphyState::Approaching:
        Approaching(DeltaTime);
        break;
    case EPorphyState::Burst:
        Burst(DeltaTime);
        break;
    }
}

void APorphy::Approaching(float DeltaTime) {
    // 1. �÷��̾� ���� ����
    FVector ToPlayer = CameraComp->GetComponentLocation() - GetActorLocation();
    FVector MoveDirection = ToPlayer.GetSafeNormal();

    // 2. õõ�� �÷��̾� �������� �̵�
    FVector Movement = MoveDirection * MoveSpeed * DeltaTime;
    AddActorWorldOffset(Movement, true);
}

void APorphy::Burst(float DeltaTime) {
    CountDown += DeltaTime;
    SpinSpeedX *= 1.02f;
    SpinSpeedY *= 1.02f;
    SpinSpeedZ *= 1.02f;
    if (CountDown > 3.0f) Boom();
}

void APorphy::Boom() {
    if (NiagaraEffect)
    {
        // 2. ���ϴ� ��ġ�� ����Ʈ ����
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            NiagaraEffect,
            GetActorLocation()
        );
    }
    OnPlayerAttacked.Broadcast(this);
    UGameplayStatics::ApplyDamage(PlayerPawn, AttackPower, nullptr, this, nullptr);
    Destroy();
}