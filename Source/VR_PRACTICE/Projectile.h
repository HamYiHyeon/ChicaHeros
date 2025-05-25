// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Projectile.generated.h"

UCLASS()
class VR_PRACTICE_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 구체 메시 컴포넌트
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SphereMesh;

	// 이동용 컴포넌트 (예: Projectile Movement)
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;
	// 플레이어 참조
	UPROPERTY()
	UCameraComponent* CameraComp;

	// 플레이어 참조
	UPROPERTY(EditAnywhere, Category = "Projectile")
	APawn* PlayerPawn;

	// 공격력
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float AttackPower = 10.f;

	// 공격 범위
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float AttackRange = 70.f;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	float Distance;
};