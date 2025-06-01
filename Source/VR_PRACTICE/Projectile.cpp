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

    // 구체 메시 생성
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    RootComponent = SphereMesh;

    // 메시 파일 로드
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereVisualAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereVisualAsset.Object);
        SphereMesh->SetWorldScale3D(FVector(0.2f)); // 크기 조절
    }

    SphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // 투사체 이동 컴포넌트 설정
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 1500.f;
    ProjectileMovement->MaxSpeed = 1500.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;

    // 충돌시 자동 제거 등 추가 설정 가능
    InitialLifeSpan = 3.0f;
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        CameraComp = PlayerPawn->FindComponentByClass<UCameraComponent>();
    }
}

void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 5. 충돌 판정
    Distance = FVector::Dist(GetActorLocation(), CameraComp->GetComponentLocation());
    if (Distance < AttackRange)
    {
        OnPlayerAttacked.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("공격!"));
        UGameplayStatics::ApplyDamage(PlayerPawn, AttackPower, nullptr, this, nullptr);
        Destroy();
    }
}