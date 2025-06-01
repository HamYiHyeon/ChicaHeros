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

    // 3. ������ ȸ�� (X, Y, Z������ õõ��)
    FRotator SpinRotation = FRotator(SpinSpeedX * DeltaTime, SpinSpeedY * DeltaTime, SpinSpeedZ * DeltaTime);
    AddActorLocalRotation(SpinRotation);

    // 1. �÷��̾� ���� ����
    FVector ToPlayer = CameraComp->GetComponentLocation() - GetActorLocation();
    FVector MoveDirection = ToPlayer.GetSafeNormal();

    // 2. õõ�� �÷��̾� �������� �̵�
    FVector Movement = MoveDirection * MoveSpeed * DeltaTime;
    AddActorWorldOffset(Movement, true);

    //�浹 ����
    Distance = FVector::Dist(GetActorLocation(), CameraComp->GetComponentLocation());
    if (Distance < AttackRange)
    {
        OnPlayerAttacked.Broadcast();
        UGameplayStatics::ApplyDamage(PlayerPawn, AttackPower, nullptr, this, nullptr);
        Destroy();
    }
}