// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // ��ü �޽� ����
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    RootComponent = SphereMesh;

    // �޽� ���� �ε�
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereVisualAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereVisualAsset.Object);
        SphereMesh->SetWorldScale3D(FVector(0.2f)); // ũ�� ����
    }

    SphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    /*
    // ����ü �̵� ������Ʈ ����
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 1500.f;
    ProjectileMovement->MaxSpeed = 1500.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;
    */
    MoveSpeed = 1500.f;
    // �浹�� �ڵ� ���� �� �߰� ���� ����
    InitialLifeSpan = 3.0f;
}

void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 1. �÷��̾� ���� ����
    FVector ToPlayer = CameraComp->GetComponentLocation() - GetActorLocation();
    FVector MoveDirection = ToPlayer.GetSafeNormal();

    // 2. õõ�� �÷��̾� �������� �̵�
    FVector Movement = MoveDirection * MoveSpeed * DeltaTime;
    AddActorWorldOffset(Movement, true);

    // 5. �浹 ����
    Distance = FVector::Dist(GetActorLocation(), CameraComp->GetComponentLocation());
    if (Distance < AttackRange)
    {
        OnPlayerAttacked.Broadcast(this);
        UE_LOG(LogTemp, Warning, TEXT("����!"));
        UGameplayStatics::ApplyDamage(PlayerPawn, AttackPower, nullptr, this, nullptr);
        Destroy();
    }
}