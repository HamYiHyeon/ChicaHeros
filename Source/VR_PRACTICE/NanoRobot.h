// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NanoRobot.generated.h"

UCLASS()
class VR_PRACTICE_API ANanoRobot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANanoRobot();

	UFUNCTION(BlueprintImplementableEvent)
	void ClearResult();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool first = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StageCleared = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DanceIndex = 0;
};
