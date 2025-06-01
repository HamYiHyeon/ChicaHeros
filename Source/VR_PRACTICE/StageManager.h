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

	// 박테리아 등록 및 해제
	void RegisterBacteria(ABacteriaBase* Bacteria);
	void UnregisterBacteria(ABacteriaBase* Bacteria);

	UPROPERTY(BlueprintReadOnly)
	TArray<ABacteriaBase*> RegisteredBacteria;

	UFUNCTION()
	void HandlePlayerAttacked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Stage")
	void OnPlayerAttackedBP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APostProcessVolume* TargetPostProcessVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APawn* PlayerPawn;

private:
	// 현재 등록된 박테리아들

	UPROPERTY(VisibleAnywhere, Category = "StageSystem")
	int StageNum = 0;
	UPROPERTY(VisibleAnywhere, Category = "StageSystem")
	float Time = 90.f;

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

	FTimerHandle SpawnTimerHandle;
	FTimerHandle DelayStartHandle;

	bool bStageStarted = false; // Stage1 스폰 여부

	int32 TotalSpawnCount;
	int32 SpawnedCount;

	TSubclassOf<ABacteriaBase> EnemyClass1;
	TSubclassOf<ABacteriaBase> EnemyClass2;
	int32 Count1;
	int32 Count2;

	int32 SpawnPhase; // 1 또는 2

	FVector SpawnOrigin;
	float SpawnRadius;
	void StartFirstStage();
	void SpawnNextEnemy();
	void SpawnEnemy(TSubclassOf<ABacteriaBase> Enemy1, int Enemy1Count, TSubclassOf<ABacteriaBase> Enemy2, int Enemy2Count);
	void TickDisable();
};
