// Fill out your copyright notice in the Description page of Project Settings.


#include "StageManager.h"

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
	
}

// Called every frame
void AStageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (StageNum == 0 && Time <= 90.f) {
		StageNum++;
		SpawnEnemy(Stage1Enemy1, Stage1Enemy1Count, Stage1Enemy2, Stage1Enemy2Count);
	} else if (StageNum == 1 && Time <= 60.f) {
		StageNum++;
		SpawnEnemy(Stage2Enemy1, Stage2Enemy1Count, Stage2Enemy2, Stage2Enemy2Count);
	} else if (StageNum == 2 && Time <= 30.f) {
		StageNum++;
		SpawnEnemy(Stage3Enemy1, Stage3Enemy1Count, Stage3Enemy2, Stage3Enemy2Count);
	}
	Time -= DeltaTime;
}

void AStageManager::SpawnEnemy(TSubclassOf<ABacteriaBase> Enemy1, int Enemy1Count, TSubclassOf<ABacteriaBase> Enemy2, int Enemy2Count)
{
	FVector Origin = GetActorLocation();
	Origin.Z += 1000.f;
	float Radius = 2000.f;

	// 스폰 범위 시각화
	DrawDebugSphere(
		GetWorld(),
		Origin,
		Radius,
		32,
		FColor::Green,
		true,   // Persistent
		-1.f,   // LifeTime (무제한)
		0,
		2.f     // Thickness
	);

	for (int i = 0; i < Enemy1Count; ++i)
	{
		FVector Offset = FMath::VRand() * FMath::FRandRange(0.f, Radius);
		FVector SpawnLoc = Origin + Offset;

		FRotator RandomRot = FRotator(FMath::FRandRange(0.f, 360.f), FMath::FRandRange(0.f, 360.f), FMath::FRandRange(0.f, 360.f));
		GetWorld()->SpawnActor<ABacteriaBase>(Enemy1, SpawnLoc, RandomRot);
	}

	for (int i = 0; i < Enemy2Count; ++i)
	{
		FVector Offset = FMath::VRand() * FMath::FRandRange(0.f, Radius);
		FVector SpawnLoc = Origin + Offset;

		FRotator RandomRot = FRotator(FMath::FRandRange(0.f, 360.f), FMath::FRandRange(0.f, 360.f), FMath::FRandRange(0.f, 360.f));
		GetWorld()->SpawnActor<ABacteriaBase>(Enemy2, SpawnLoc, RandomRot);
	}
}

