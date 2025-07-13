#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "ProgressToothActor.h"
#include "ProgressRotatingActor.h"
#include "ProgressRotatingActor2.h"
#include "HandPoseJudgeActor.generated.h"

class USkeletalMeshComponent;
class ASpawn_Spline; // ✅ 너가 만든 손 생성 액터 클래스!

UCLASS()
class VR_PRACTICE_API AHandPoseJudgeActor : public AActor
{
	GENERATED_BODY()

public:
	AHandPoseJudgeActor();
	bool Logonce = false;
	USkeletalMeshComponent* GetNearestSpawnedHand();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void CompareHandsAndUpdateProgress();

	UPROPERTY(EditAnywhere, Category = "Hand Matching")
	TArray<FName> BoneNamesToCompare_l;

	UPROPERTY(EditAnywhere, Category = "Hand Matching")
	TArray<FName> BoneNamesToCompare_r;

	UPROPERTY(EditAnywhere, Category = "Matching Settings")
	float PositionTolerance = 20.f;

	UPROPERTY(EditAnywhere, Category = "Matching Settings")
	float RotationTolerance = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Progress")
	float Progress = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Matching Settings")
	float MatchingDistanceThreshold = 20.f; // 손 전체 위치 차이 허용

	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraSystem* MatchingEffect;

	UPROPERTY()
	AProgressToothActor* ToothProgressActor;
	
	UPROPERTY()
	AProgressRotatingActor* RotatingActor;

	UPROPERTY()
	AProgressRotatingActor2* RotatingActor2;
	
private:
	USkeletalMeshComponent* VRHandMesh_L = nullptr;
	USkeletalMeshComponent* VRHandMesh_R = nullptr;
	ASpawn_Spline* SpawnedSplineActor_L = nullptr;
	ASpawn_Spline* SpawnedSplineActor_R = nullptr;

	bool AreHandsMatching();
	FBodyInstance* GetBodyInstance(USkeletalMeshComponent* Mesh, const FName& BoneName);
};
