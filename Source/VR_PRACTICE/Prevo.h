// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BacteriaBase.h"
#include "Prevo.generated.h"

/**
 *
 */
UCLASS()
class VR_PRACTICE_API APrevo : public ABacteriaBase
{
	GENERATED_BODY()

public:
	APrevo();

protected:
    virtual float TakeDamageBac(float DamageAmount) override;
;
	virtual void Tick(float DeltaTime) override;

    void Split();

    UPROPERTY(EditAnywhere, Category = "Sprit")
    float SpinSpeedX = 30.f;

    UPROPERTY(EditAnywhere, Category = "Sprit")
    float SpinSpeedY = 45.f;

    UPROPERTY(EditAnywhere, Category = "Sprit")
    float SpinSpeedZ = 60.f;


    UPROPERTY(EditAnywhere, Category = "Split")
    int32 CurrentSplitLevel = 0;

    UPROPERTY(EditAnywhere, Category = "Split")
    int32 MaxSplitLevel = 2;

    UPROPERTY(EditAnywhere, Category = "Split")
    TSubclassOf<APrevo> SplitBacteriaClass;

    UPROPERTY(EditAnywhere, Category = "Split")
    float InitialHealth = 100.f;

    UPROPERTY(EditAnywhere, Category = "Split")
    float InitialAttackPower = 15.f;

    UPROPERTY(EditAnywhere, Category = "Split")
    float ScaleMultiplierPerSplit = 0.7f;

    UPROPERTY(EditAnywhere, Category = "Split")
    float StatMultiplierPerSplit = 0.5f;


private:
    bool bIsSpawning = false;
    float SpreadElapsedTime = 0.f;
    float SpreadDuration = 1.f;
    FVector InitialLocation;
    FVector TargetSpreadLocation;
    float SpreadInterpSpeed = 3.0f;

    bool bIsFlyingToPlayer = true;
};