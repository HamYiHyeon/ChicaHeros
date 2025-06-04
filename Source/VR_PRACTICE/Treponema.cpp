// Fill out your copyright notice in the Description page of Project Settings.


#include "Treponema.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Projectile.h"

ATreponema::ATreponema() {
    ProjectileClass = AProjectile::StaticClass();

    Health = 150.0f;
    AttackRange = 1500.f;
    MoveSpeed = 300.f;
    CurMoveSpeed = MoveSpeed;
}

void ATreponema::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (!PlayerPawn || !CameraComp) return;

    FVector ToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
    Distance = FVector::Dist(GetActorLocation(), CameraComp->GetComponentLocation());
    if (CurMoveSpeed <= 0.f) {
        if (Distance > AttackRange)
        {
            CurrentState = ETreponemaState::Approaching;
        }
        else
        {
            CurrentState = ETreponemaState::Attacking;
        }
    }

    switch (CurrentState)
    {
    case ETreponemaState::Approaching:
        MoveToward(CameraComp->GetComponentLocation(), DeltaTime);
        break;

    case ETreponemaState::Attacking:
        HandleAttackState(DeltaTime);
        break;
    }
}

void ATreponema::HandleAttackState(float DeltaTime)
{
    // 랜덤 목표 위치에 천천히 이동
    if ((GetActorLocation() - RandomMoveTarget).Size() < 50.f || FMath::FRand() < 0.01f)
    {
        FVector RandOffset = UKismetMathLibrary::RandomUnitVector() * 600.f;
        RandomMoveTarget = GetActorLocation() + RandOffset;
        if (RandomMoveTarget.Z <= CameraComp->GetComponentLocation().Z + 10.f)
            RandomMoveTarget.Z = CameraComp->GetComponentLocation().Z + FMath::RandRange(10.f, 40.f);
    }

    MoveToward(RandomMoveTarget, DeltaTime);

    // 투사체 쿨다운
    FireTimer += DeltaTime;
    //UE_LOG(LogTemp, Warning, TEXT("FireTimer: %.2f"), FireTimer);
    if (FireTimer >= FireInterval)
    {
        FireProjectileAt(CameraComp->GetComponentLocation());
        FireTimer = 0.f;
    }
}

void ATreponema::MoveToward(FVector TargetLocation, float DeltaTime)
{
    if (!CameraComp) return;

    // 1. 플레이어 방향 벡터
    FVector ToPlayer = TargetLocation - GetActorLocation();

    // 2. 정수리 방향이 타겟을 향하도록 회전 계산
    FRotator TargetRot = FRotationMatrix::MakeFromZ(ToPlayer).Rotator();

    // 3. 부드럽게 회전
    FRotator SmoothRot = FMath::RInterpTo(GetActorRotation(), TargetRot, DeltaTime, TrackingSpeed);
    SetActorRotation(SmoothRot);

    if (CurMoveSpeed > 0) {
        // 4. 항상 현재 정수리 방향으로 이동
        FVector Movement = GetActorUpVector() * CurMoveSpeed * DeltaTime;
        AddActorWorldOffset(Movement, true);

        CurMoveSpeed -= 2.0f;
    }
    else {
        CurMoveSpeed = MoveSpeed;
    }
}

void ATreponema::FireProjectileAt(FVector Target)
{
    if (!ProjectileClass) return;

    FVector SpawnLoc = GetActorLocation() + FVector(0, 0, 0); // 약간 위에서
    FRotator SpawnRot = (Target - SpawnLoc).Rotation();

    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoc, SpawnRot);
    if (Projectile)
    {
        FVector LaunchDir = (Target - SpawnLoc).GetSafeNormal();
        Projectile->SphereMesh->IgnoreActorWhenMoving(this, true);
    }
}
