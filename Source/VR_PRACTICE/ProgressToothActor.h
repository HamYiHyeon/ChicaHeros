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
	
	// ������� HandPose ��ġ ���൵
	UPROPERTY(EditAnywhere, Category = "Tooth")
	float CurrentProgress = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "Tooth")
	float MaxHeight = 50.f;

	UPROPERTY(EditAnywhere, Category = "Tooth")
	float MoveSpeed = 100.f; 

	// ���൵ ������Ʈ �� ȣ��
	UFUNCTION(BlueprintCallable)
	void OnProgressUpdated(float NewProgress);

	TArray<FVector> InitialToothLocations;
	TArray<FVector> TargetToothLocations;
};
