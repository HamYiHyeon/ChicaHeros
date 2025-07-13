#include "ProgressToothActor.h"

AProgressToothActor::AProgressToothActor()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void AProgressToothActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<USceneComponent*> ChildrenComp;
	GetRootComponent()->GetChildrenComponents(true, ChildrenComp);

	for (USceneComponent* Comp : ChildrenComp) 
	{
		if (UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Comp)) 
		{
			if (MeshComp->GetName().Contains(TEXT("Tooth"))) 
			{
				ToothMeshes.Add(MeshComp);		// 뽑을 이빨 메시 할당
				InitialToothLocations.Add(MeshComp->GetRelativeLocation());		// 이빨 메시 초기 위치 저장
				TargetToothLocations.Add(MeshComp->GetRelativeLocation());		//초기 목표도 초기 위치
				UE_LOG(LogTemp, Log, TEXT("Tooth 자동으로 등록됨!"));
			}
		}
	}
}

void AProgressToothActor::OnProgressUpdated(float NewProgress)
{
	CurrentProgress = FMath::Clamp(NewProgress, 0.f, 100.f);

	UE_LOG(LogTemp, Warning, TEXT("전달받은 진행도 :%f"), CurrentProgress);
	UE_LOG(LogTemp, Warning, TEXT("🦷 ToothMeshes 개수: %d"), ToothMeshes.Num());

	if (ToothMeshes.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("❌ ToothMeshes에 등록된 메시가 없습니다!"));
		return;
	}

	const float NormalizedProgress = CurrentProgress / 100.0f;
	const int32 ToothIndex = FMath::FloorToInt(NormalizedProgress * ToothMeshes.Num());

	if (!ToothMeshes.IsValidIndex(ToothIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("❌ ToothIndex %d is invalid!"), ToothIndex);
		return;
	}

	float LocalProgress = (NormalizedProgress * ToothMeshes.Num()) - ToothIndex;

	FVector StartLocation = InitialToothLocations[ToothIndex];
	FVector EndLocation = StartLocation + FVector(0.f, 0.f, MaxHeight * LocalProgress);

	UE_LOG(LogTemp, Warning, TEXT("📦 회전용 진행도 갱신: %f"), CurrentProgress);
	UE_LOG(LogTemp, Warning, TEXT("StartLoc: %s, EndLoc: %s"), *StartLocation.ToString(), *EndLocation.ToString());

	TargetToothLocations[ToothIndex] = EndLocation;
}


void AProgressToothActor::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < ToothMeshes.Num(); ++i)
	{
		if (!ToothMeshes[i]) continue;

		FVector CurrentLoc = ToothMeshes[i]->GetRelativeLocation();
		FVector TargetLoc = TargetToothLocations[i];

		// 보간
		FVector NewLoc = FMath::VInterpTo(CurrentLoc, TargetLoc, DeltaTime, MoveSpeed);
		ToothMeshes[i]->SetRelativeLocation(NewLoc);
	}
}





