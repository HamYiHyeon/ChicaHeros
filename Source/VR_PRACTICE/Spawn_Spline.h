#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawn_Spline.generated.h"

class UArrowComponent;
class USceneComponent;

USTRUCT()
struct FMovingTooth
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* Actor;

	UPROPERTY()
	USkeletalMeshComponent* MeshComp;

	UPROPERTY()
	float ElapsedTime;

	UPROPERTY()
	FRotator InitialRotation = FRotator::ZeroRotator; // ✅ 추가

	FMovingTooth()
		: Actor(nullptr), MeshComp(nullptr), ElapsedTime(0.f), InitialRotation(FRotator::ZeroRotator)
	{
	}
};


UCLASS()
class VR_PRACTICE_API ASpawn_Spline : public AActor
{
	GENERATED_BODY()

public:
	ASpawn_Spline();
	TArray<FMovingTooth> SpawnedTeeth;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SpawnHand();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* Arrow;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	USkeletalMesh* Target_L;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnInterval = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxTravelDistance = 1000.0f;

	float SpawnTimer = 0.0f;
};
