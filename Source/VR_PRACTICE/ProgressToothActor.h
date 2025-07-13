#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProgressToothActor.generated.h"

UCLASS()
class VR_PRACTICE_API AProgressToothActor : public AActor
{
	GENERATED_BODY()

public:
	AProgressToothActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Tooth")
	TArray<UStaticMeshComponent*> ToothMeshes;
	
	// 현재까지 HandPose 일치 진행도
	UPROPERTY(EditAnywhere, Category = "Tooth")
	float CurrentProgress = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "Tooth")
	float MaxHeight = 50.f;

	UPROPERTY(EditAnywhere, Category = "Tooth")
	float MoveSpeed = 100.f; 

	// 진행도 업데이트 시 호출
	UFUNCTION(BlueprintCallable)
	void OnProgressUpdated(float NewProgress);

	TArray<FVector> InitialToothLocations;
	TArray<FVector> TargetToothLocations;
};
