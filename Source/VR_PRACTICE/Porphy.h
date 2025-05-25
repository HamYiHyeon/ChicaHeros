// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BacteriaBase.h"
#include "Porphy.generated.h"

/**
 *
 */
UCLASS()
class VR_PRACTICE_API APorphy : public ABacteriaBase
{
	GENERATED_BODY()

public:
	APorphy();

protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Burst")
	float SpinSpeedX = 30.f;

	UPROPERTY(EditAnywhere, Category = "Burst")
	float SpinSpeedY = 45.f;

	UPROPERTY(EditAnywhere, Category = "Burst")
	float SpinSpeedZ = 60.f;
};