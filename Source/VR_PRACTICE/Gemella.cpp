// Fill out your copyright notice in the Description page of Project Settings.


#include "Gemella.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

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

    // ���� �ð����� ��ȣ�� �ο� �Լ� ����
    GetWorld()->GetTimerManager().SetTimer(
        ShieldGrantTimer,
        this,
        &AGemella::GrantShieldsToNearbyBacteria,
        ShieldGrantInterval,
        true // �ݺ� ȣ��
    );
}

void AGemella::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!PlayerPawn || !CameraComp) return;
    if (Wait > 0.f) {
        Wait -= DeltaTime;
        return;
    }
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

        if (Bacteria->Shield <= 0.f) // ��ȣ���� ���� ���� �ο�
        {
            Bacteria->Shield = Bacteria->MaxShield;
            UE_LOG(LogTemp, Log, TEXT("[Gemella] %s���� ��ȣ�� �ο�"), *Bacteria->GetName());
        }
    }
}

void AGemella::MoveToward(FVector TargetLocation, float DeltaTime)
{
    if (!CameraComp) return;

    // 1. �÷��̾� ���� ����
    FVector ToPlayer = TargetLocation - GetActorLocation();

    // 2. ������ ������ Ÿ���� ���ϵ��� ȸ�� ���
    FRotator TargetRot = FRotationMatrix::MakeFromZ(ToPlayer).Rotator();

    // 3. �ε巴�� ȸ��
    FRotator SmoothRot = FMath::RInterpTo(GetActorRotation(), TargetRot, DeltaTime, TrackingSpeed);
    SetActorRotation(SmoothRot);

    FVector Movement = GetActorUpVector() * MoveSpeed * DeltaTime;
    AddActorWorldOffset(Movement, true);
}

void AGemella::HandleAttackState(float DeltaTime)
{
    // ���� ��ǥ ��ġ�� õõ�� �̵�
    if ((GetActorLocation() - RandomMoveTarget).Size() < 50.f || FMath::FRand() < 0.01f)
    {
        FVector RandOffset = UKismetMathLibrary::RandomUnitVector() * 600.f;
        RandomMoveTarget = GetActorLocation() + RandOffset;
    }

    MoveToward(RandomMoveTarget, DeltaTime);
}