// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BacteriaBase.h"
#include "Porphy.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class EPorphyState : uint8
{
	Approaching,
	Burst
};

UCLASS()
class VR_PRACTICE_API APorphy : public ABacteriaBase
{
	GENERATED_BODY()

public:
	APorphy();

protected:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	EPorphyState CurrentState = EPorphyState::Approaching;

	void Burst(float DeltaTime);
	void Approaching(float DeltaTime);
	void Boom();
	float CountDown = 0.f;

	UNiagaraSystem* NiagaraEffect;
};