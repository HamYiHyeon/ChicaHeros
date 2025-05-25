// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BacteriaBase.h"
#include "Projectile.h"
#include "Treponema.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class ETreponemaState : uint8
{
	Approaching,
	Attacking
};

UCLASS()
class MONSTERC_API ATreponema : public ABacteriaBase
{
	GENERATED_BODY()

public:
	ATreponema();

protected:
	UPROPERTY(VisibleAnywhere)
	ETreponemaState CurrentState = ETreponemaState::Approaching;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	float FireInterval = 2.0f;

	float FireTimer = 0.f;

	float CurMoveSpeed;

	bool Compelete = false;

	FVector RandomMoveTarget;

	virtual void Tick(float DeltaTime) override;

	void HandleAttackState(float DeltaTime);
	void MoveToward(FVector TargetLocation, float DeltaTime);
	void FireProjectileAt(FVector Target);
};