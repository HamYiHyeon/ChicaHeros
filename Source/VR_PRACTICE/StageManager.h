// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BacteriaBase.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stage")
	TArray<TSubclassOf<ABacteriaBase>> Enemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stage")
	int EnemyCount;

	UPROPERTY(BlueprintReadOnly)
	TArray<ABacteriaBase*> RegisteredBacteria;

	UFUNCTION()
	void HandlePlayerAttacked(ABacteriaBase* Attacker);

	UFUNCTION(BlueprintImplementableEvent, Category = "Stage")
	void OnPlayerAttackedBP(float Damage);

	UFUNCTION(BlueprintImplementableEvent, Category = "Stage")
	void GameResult();

	UFUNCTION(BlueprintImplementableEvent, Category = "Stage")
	void TimeOver();

	UFUNCTION(BlueprintImplementableEvent, Category = "Stage")
	void GameClear();

	UFUNCTION(BlueprintImplementableEvent, Category = "Stage")
	void MonsterInfo();

	//UFUNCTION(BlueprintImplementableEvent, Category = "Stage")
	//void SpawnEnemy();
	void SpawnEnemy();

	UFUNCTION(BlueprintCallable, Category = "Stage")
	void TickDisable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APostProcessVolume* TargetPostProcessVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APawn* PlayerPawn;

	UPROPERTY(VisibleAnywhere, Category = "StageSystem")
	float Time = 100.f;

	UPROPERTY(BlueprintReadWrite)
	bool bCleared = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StageSystem")
	int StageNum = 0;

private:
	UNiagaraSystem* NiagaraEffect;

	FTimerHandle SpawnTimerHandle;
	FTimerHandle DelayStartHandle;

	bool bStageStarted = false; // Stage1 스폰 여부

	//int32 SpawnedCount;

	int32 Count;

	int32 SpawnPhase; // 1 또는 2
	bool bAllSpawned = false;

	FVector SpawnOrigin;
	float SpawnRadius;
	void StartFirstStage();
	void SpawnNextEnemy();
};

