// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.


#include "StageManager.h"
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

	// 1. ���� ��η� ���̾ư��� �ý��� �ҷ�����
	NiagaraEffect = LoadObject<UNiagaraSystem>(
		nullptr,
		TEXT("/Game/Niagara/NS_Cloud.NS_Cloud")
	);

	// 3�� �� Stage ����
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
	UE_LOG(LogTemp, Warning, TEXT("�÷��̾ ���׸��ƿ��� ���ݴ���!"));
	float Damage = Attacker->AttackPower;
	OnPlayerAttackedBP(Damage); // �������Ʈ ���� ȣ��
}

// Called every frame
void AStageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bStageStarted) return; // 3�� ������ ������ �ƹ��͵� �� ��

	if(!bCleared) Time += DeltaTime;

	if (StageNum == 1 && Time > 30.f) {
		SpawnEnemy();
	}
	else if (StageNum == 2 && Time > 60.f) {
		SpawnEnemy();
	}

	if (bAllSpawned && RegisteredBacteria.IsEmpty()) {
		/*
		UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
		if (GI) {
			GI->bStageCleared = true;
		}
		*/
		bCleared = true;
		GameClear();
	}
}

void AStageManager::StartFirstStage()
{
	// Stage1 ���� �������� Time �ʱ�ȭ �� ����
	Time = 0.f;
	StageNum = 0;
	bStageStarted = true;

	SpawnEnemy();
}

void AStageManager::SpawnNextEnemy()
{
	int rand = FMath::RandRange(0, 1);
	TSubclassOf<ABacteriaBase> CurrentClass = Enemy[rand];
	if (CurrentClass && CurrentClass->FindPropertyByName(FName("CurrentState"))) {
		if(CurrentClass->FindPropertyByName(FName("ShieldGrantInterval")))
			if (FMath::RandRange(0, 4) > 0) CurrentClass = Enemy[(rand + 1) % 2];
	}
	FVector Offset = FMath::VRand() * FMath::FRandRange(0.f, SpawnRadius);
	FVector SpawnLoc = SpawnOrigin + Offset;
	FRotator RandomRot = FRotator(
		FMath::FRandRange(0.f, 360.f),
		FMath::FRandRange(0.f, 360.f),
		FMath::FRandRange(0.f, 360.f)
	);
	GetWorld()->SpawnActor<ABacteriaBase>(CurrentClass, SpawnLoc, RandomRot);
	if (NiagaraEffect)
	{
		// 2. ���ϴ� ��ġ�� ����Ʈ ����
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			NiagaraEffect,
			SpawnLoc,   // ���� ���� ��ġ(���ϴ� ��ġ�� ���� ����)
			RandomRot
		);
	}
	EnemyCount--;

	if (EnemyCount <= 0)
	{
		if (StageNum == 2) bAllSpawned = true;
		MonsterInfo();
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void AStageManager::SpawnEnemy()
{
	StageNum++;
	SpawnOrigin = GetActorLocation() + FVector(0.f, 0.f, 1400.f);
	SpawnRadius = 1900.f;

	// ���� ���� �ð�ȭ
	DrawDebugSphere(
		GetWorld(),
		SpawnOrigin,
		SpawnRadius,
		32,
		FColor::Green,
		true,   // Persistent
		-1.f,   // LifeTime (������)
		0,
		2.f     // Thickness
	);
	//EnemyClass2 = Enemy2;
	//Count2 = Enemy2Count;

	//SpawnPhase = 1; // 1�ܰ�: Enemy1
	//TotalSpawnCount = Count1;

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle, this,
		&AStageManager::SpawnNextEnemy,
		28.f / EnemyCount, true
	);
}


void AStageManager::TickDisable()
{
	for (ABacteriaBase* Bacteria : RegisteredBacteria)
	{
		if (IsValid(Bacteria))
		{
			Bacteria->SetActorTickEnabled(false); // �Ǵ� Bacteria->MoveSpeed = 0.f;
		}
	}
}
