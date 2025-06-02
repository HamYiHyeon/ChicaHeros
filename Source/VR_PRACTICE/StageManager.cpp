// Fill out your copyright notice in the Description page of Project Settings.


#include "StageManager.h"
#include "MyGameInstance.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AStageManager::AStageManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStageManager::BeginPlay()
{
	Super::BeginPlay();

	// 3초 후 Stage 시작
	GetWorldTimerManager().SetTimer(DelayStartHandle, this, &AStageManager::StartFirstStage, 3.0f, false);
}

void AStageManager::RegisterBacteria(ABacteriaBase* Bacteria)
{
	if (Bacteria && !RegisteredBacteria.Contains(Bacteria))
	{
		RegisteredBacteria.Add(Bacteria);
	}
	Bacteria->OnPlayerAttacked.AddDynamic(this, &AStageManager::HandlePlayerAttacked);
}

void AStageManager::UnregisterBacteria(ABacteriaBase* Bacteria)
{
	if (Bacteria)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroyed: %s"), *Bacteria->GetName());
		RegisteredBacteria.Remove(Bacteria);
	}
}

void AStageManager::HandlePlayerAttacked(ABacteriaBase* Attacker)
{
	UE_LOG(LogTemp, Warning, TEXT("플레이어가 박테리아에게 공격당함!"));
	float Damage = Attacker->AttackPower;
	OnPlayerAttackedBP(Damage); // 블루프린트 연출 호출
}

// Called every frame
void AStageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bStageStarted) return; // 3초 딜레이 전에는 아무것도 안 함

	if(!bCleared) Time -= DeltaTime;

	if (StageNum == 1 && Time <= 60.f) {
		StageNum++;
		SpawnEnemy(Stage2Enemy1, Stage2Enemy1Count, Stage2Enemy2, Stage2Enemy2Count);
	}
	else if (StageNum == 2 && Time <= 30.f) {
		StageNum++;
		SpawnEnemy(Stage3Enemy1, Stage3Enemy1Count, Stage3Enemy2, Stage3Enemy2Count);
	}

	if (bAllSpawned && RegisteredBacteria.IsEmpty()) {
		UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
		if (GI) {
			GI->bStageCleared = true;
		}
		bCleared = true;
		GameClear();
	}
	else if(Time <= 0.f) {
		UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
		if (GI) {
			GI->bStageCleared = false;
		}
		bCleared = true;
		TimeOver();
	}
}

void AStageManager::StartFirstStage()
{
	// Stage1 시작 시점에서 Time 초기화 및 스폰
	Time = 90.f;
	StageNum = 0;
	bStageStarted = true;

	SpawnEnemy(Stage1Enemy1, Stage1Enemy1Count, Stage1Enemy2, Stage1Enemy2Count);
	StageNum++;
}

void AStageManager::SpawnNextEnemy()
{
	TSubclassOf<ABacteriaBase> CurrentClass = (SpawnPhase == 1) ? EnemyClass1 : EnemyClass2;

	if (SpawnedCount >= TotalSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

		if (StageNum == 3 && SpawnPhase == 2) bAllSpawned = true;
		if (SpawnPhase == 1)
		{
			// Enemy1 다 소환했으므로 Enemy2 시작
			SpawnPhase = 2;
			SpawnedCount = 0;
			TotalSpawnCount = Count2;

			GetWorld()->GetTimerManager().SetTimer(
				SpawnTimerHandle, this,
				&AStageManager::SpawnNextEnemy,
				0.3f, true
			);
		}

		return;
	}

	FVector Offset = FMath::VRand() * FMath::FRandRange(0.f, SpawnRadius);
	FVector SpawnLoc = SpawnOrigin + Offset;
	FRotator RandomRot = FRotator(
		FMath::FRandRange(0.f, 360.f),
		FMath::FRandRange(0.f, 360.f),
		FMath::FRandRange(0.f, 360.f)
	);

	GetWorld()->SpawnActor<ABacteriaBase>(CurrentClass, SpawnLoc, RandomRot);
	SpawnedCount++;
}

void AStageManager::SpawnEnemy(TSubclassOf<ABacteriaBase> Enemy1, int Enemy1Count, TSubclassOf<ABacteriaBase> Enemy2, int Enemy2Count)
{
	SpawnOrigin = GetActorLocation() + FVector(0.f, 0.f, 1300.f);
	SpawnRadius = 2000.f;

	// 스폰 범위 시각화
	DrawDebugSphere(
		GetWorld(),
		SpawnOrigin,
		SpawnRadius,
		32,
		FColor::Green,
		true,   // Persistent
		-1.f,   // LifeTime (무제한)
		0,
		2.f     // Thickness
	);

	EnemyClass1 = Enemy1;
	Count1 = Enemy1Count;
	EnemyClass2 = Enemy2;
	Count2 = Enemy2Count;

	SpawnPhase = 1; // 1단계: Enemy1
	SpawnedCount = 0;
	TotalSpawnCount = Count1;

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle, this,
		&AStageManager::SpawnNextEnemy,
		0.3f, true
	);
}

void AStageManager::TickDisable()
{
	for (ABacteriaBase* Bacteria : RegisteredBacteria)
	{
		if (IsValid(Bacteria))
		{
			Bacteria->SetActorTickEnabled(false); // 또는 Bacteria->MoveSpeed = 0.f;
		}
	}
}
