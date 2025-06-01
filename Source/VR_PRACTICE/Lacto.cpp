// Fill out your copyright notice in the Description page of Project Settings.


#include "Lacto.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ALacto::ALacto() {
    PrimaryActorTick.bCanEverTick = true;

    Health = 150.0f;
    MaxSpeed = 1000.0f;
    MoveSpeed = 0.f;
}

void ALacto::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!PlayerPawn || !CameraComp) return;
    if (MaxSpeed > MoveSpeed) MoveSpeed += IncSpeed;

    // 1. �÷��̾� ���� ����
    FVector ToPlayer = CameraComp->GetComponentLocation() - GetActorLocation();

    // 2. ������ ������ Ÿ���� ���ϵ��� ȸ�� ���
    FRotator TargetRot = FRotationMatrix::MakeFromZ(ToPlayer).Rotator();

    // 3. �ε巴�� ȸ��
    FRotator SmoothRot = FMath::RInterpTo(GetActorRotation(), TargetRot, DeltaTime, TrackingSpeed);
    SetActorRotation(SmoothRot);

    // 4. �׻� ���� ������ �������� �̵�
    FVector Movement = GetActorUpVector() * MoveSpeed * DeltaTime;
    AddActorWorldOffset(Movement, true);

    // 5. �浹 ����
    Distance = FVector::Dist(GetActorLocation(), CameraComp->GetComponentLocation());
    //UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance);
    if (Distance < AttackRange)
    {
        OnPlayerAttacked.Broadcast();
        UGameplayStatics::ApplyDamage(PlayerPawn, AttackPower, nullptr, this, nullptr);
        Destroy();
    }
}