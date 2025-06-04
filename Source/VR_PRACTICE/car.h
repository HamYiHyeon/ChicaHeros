// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "car.generated.h"

UCLASS()
class VR_PRACTICE_API Acar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float movespeed = 1500.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
