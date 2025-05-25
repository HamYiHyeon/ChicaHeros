// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BacteriaBase.h"
#include "Gemella.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGemellaState : uint8
{
	Approaching,
	Wander
};

UCLASS()
class VR_PRACTICE_API AGemella : public ABacteriaBase
{
	GENERATED_BODY()
	
public:
	AGemella();

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	void GrantShieldsToNearbyBacteria();

	UPROPERTY(VisibleAnywhere)
	EGemellaState CurrentState = EGemellaState::Approaching;

	void HandleAttackState(float DeltaTime);
	void MoveToward(FVector TargetLocation, float DeltaTime);

	FTimerHandle ShieldGrantTimer;
	UPROPERTY(EditAnywhere, Category = "Shield")
	float ShieldGrantInterval = 10.0f;

	FVector RandomMoveTarget;
};
