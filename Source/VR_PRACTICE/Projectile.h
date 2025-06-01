// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "BacteriaBase.h"
#include "Projectile.generated.h"

UCLASS()
class VR_PRACTICE_API AProjectile : public ABacteriaBase
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
};