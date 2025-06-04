// Fill out your copyright notice in the Description page of Project Settings.


#include "Prevo.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/KismetMathLibrary.h>

APrevo::APrevo() {
    PrimaryActorTick.bCanEverTick = true;

    SplitBacteriaClass = APrevo::StaticClass();
    Health = InitialHealth;
    MoveSpeed = 100.0f;
    AttackPower = InitialAttackPower;

    UE_LOG(LogTemp, Warning, TEXT("Prevo Spawn"));
}

void APrevo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //전방위 회전 (X, Y, Z축으로 천천히)
    FRotator SpinRotation = FRotator(SpinSpeedX * DeltaTime, SpinSpeedY * DeltaTime, SpinSpeedZ * DeltaTime);
    AddActorLocalRotation(SpinRotation);

    if (!PlayerPawn || !CameraComp) return;
    if (MaxSpeed > MoveSpeed) MoveSpeed += IncSpeed;

    //테스트용 삭제 필요
    //TakeDamageBac(0.2f);

    if (bIsSpawning)
    {
        SpreadElapsedTime += DeltaTime;

        FVector NewLoc = FMath::VInterpTo(GetActorLocation(), TargetSpreadLocation, DeltaTime, SpreadInterpSpeed);
        SetActorLocation(NewLoc, true);

        if (SpreadElapsedTime >= SpreadDuration)
        {
            bIsSpawning = false;
            bIsFlyingToPlayer = true;
        }

        return;
    }

    // 1. 플레이어 방향 벡터
    FVector ToPlayer = CameraComp->GetComponentLocation() - GetActorLocation();
    if (bIsFlyingToPlayer && PlayerPawn)
    {
        FVector MoveDirection = ToPlayer.GetSafeNormal();

        // 2. 천천히 플레이어 방향으로 이동
        FVector Movement = MoveDirection * MoveSpeed * DeltaTime;
        AddActorWorldOffset(Movement, true);
    }
        // 4. 충돌 거리 판정
    Distance = FVector::Dist(GetActorLocation(), CameraComp->GetComponentLocation());
    if (Distance < AttackRange)
    {
        bIsFlyingToPlayer = false;
        OnPlayerAttacked.Broadcast(this);
        UGameplayStatics::ApplyDamage(PlayerPawn, AttackPower, nullptr, this, nullptr);
        Destroy();
    }
}

void APrevo::OnDeath()
{
    if (CurrentSplitLevel < MaxSplitLevel)
    {
        UE_LOG(LogTemp, Warning, TEXT("Split"));
        Split();
    }
}


void APrevo::Split()
{
    FVector SpawnLocation = GetActorLocation();

    for (int i = 0; i < 2; i++)
    {
        FVector RandomDir = UKismetMathLibrary::RandomUnitVector() * 100.f;

        FTransform SpawnTransform;
        SpawnTransform.SetLocation(SpawnLocation + RandomDir);
        SpawnTransform.SetRotation(FQuat::Identity);
        SpawnTransform.SetScale3D(GetActorScale3D() * ScaleMultiplierPerSplit);

        APrevo* NewClone = GetWorld()->SpawnActorDeferred<APrevo>(
            SplitBacteriaClass, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

        if (NewClone)
        {
            NewClone->bIsSpawning = true;
            NewClone->SpreadElapsedTime = 0.f;
            NewClone->InitialLocation = SpawnLocation;
            NewClone->TargetSpreadLocation = SpawnLocation + RandomDir * 4.0f; // 퍼지는 방향 거리

            NewClone->CurrentSplitLevel = this->CurrentSplitLevel + 1;
            NewClone->InitialHealth = InitialHealth * FMath::Pow(StatMultiplierPerSplit, NewClone->CurrentSplitLevel);
            NewClone->AttackPower = InitialAttackPower * FMath::Pow(StatMultiplierPerSplit, NewClone->CurrentSplitLevel);
            NewClone->MoveSpeed = MoveSpeed;
            UGameplayStatics::FinishSpawningActor(NewClone, SpawnTransform);
        }
    }
}