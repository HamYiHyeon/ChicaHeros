// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BacteriaBase.h"
#include "StageManager.generated.h"

UCLASS()
class VR_PRACTICE_API AStageManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "StageSystem")
	int StageNum = 0;
	UPROPERTY(VisibleAnywhere, Category = "StageSystem")
	float Time = 90.f;;

	UPROPERTY(EditAnywhere, Category = "Stage1")
	TSubclassOf<ABacteriaBase> Stage1Enemy1;
	UPROPERTY(EditAnywhere, Category = "Stage1")
	int Stage1Enemy1Count = 1;
	UPROPERTY(EditAnywhere, Category = "Stage1")
	TSubclassOf<ABacteriaBase> Stage1Enemy2;
	UPROPERTY(EditAnywhere, Category = "Stage1")
	int Stage1Enemy2Count = 1;

	UPROPERTY(EditAnywhere, Category = "Stage2")
	TSubclassOf<ABacteriaBase> Stage2Enemy1;
	UPROPERTY(EditAnywhere, Category = "Stage2")
	int Stage2Enemy1Count = 1;
	UPROPERTY(EditAnywhere, Category = "Stage2")
	TSubclassOf<ABacteriaBase> Stage2Enemy2;
	UPROPERTY(EditAnywhere, Category = "Stage2")
	int Stage2Enemy2Count = 1;

	UPROPERTY(EditAnywhere, Category = "Stage3")
	TSubclassOf<ABacteriaBase> Stage3Enemy1;
	UPROPERTY(EditAnywhere, Category = "Stage3")
	int Stage3Enemy1Count = 1;
	UPROPERTY(EditAnywhere, Category = "Stage3")
	TSubclassOf<ABacteriaBase> Stage3Enemy2;
	UPROPERTY(EditAnywhere, Category = "Stage3")
	int Stage3Enemy2Count = 1;

	void SpawnEnemy(TSubclassOf<ABacteriaBase> Enemy1, int Enemy1Count, TSubclassOf<ABacteriaBase> Enemy2, int Enemy2Count);
};
