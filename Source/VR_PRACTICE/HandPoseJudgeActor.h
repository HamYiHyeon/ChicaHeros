#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandPoseJudgeActor.generated.h"

class USkeletalMeshComponent;
class ASpawn_Spline; // ✅ 너가 만든 손 생성 액터 클래스!

UCLASS()
class VR_PRACTICE_API AHandPoseJudgeActor : public AActor
{
	GENERATED_BODY()

public:
	AHandPoseJudgeActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void CompareHandsAndUpdateProgress();

	UPROPERTY(EditAnywhere, Category = "Hand Matching")
	TArray<FName> BoneNamesToCompare;

	UPROPERTY(EditAnywhere, Category = "Matching Settings")
	float PositionTolerance = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Matching Settings")
	float RotationTolerance = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Progress")
	float Progress = 0.0f;

private:
	USkeletalMeshComponent* VRHandMesh = nullptr;
	ASpawn_Spline* SpawnedSplineActor = nullptr;

	bool AreHandsMatching();
	FBodyInstance* GetBodyInstance(USkeletalMeshComponent* Mesh, const FName& BoneName);
};
