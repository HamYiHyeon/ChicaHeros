#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProgressRotatingActor.generated.h"

UCLASS()
class VR_PRACTICE_API AProgressRotatingActor : public AActor
{
	GENERATED_BODY()

public:
	AProgressRotatingActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// 회전할 메시 (자동 할당 대상)
	UPROPERTY(EditAnywhere, Category = "Rotation")
	UStaticMeshComponent* RotateComp;

	// 초기 회전값
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator InitialRotation = FRotator::ZeroRotator;

	// 최대 회전 오프셋 (진행도 중간에서 최대)
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator MaxRotationOffset = FRotator(0.f, 0.f, 50.f);

	// 회전 보간 속도
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationInterpSpeed = 5.f;

	// 현재 진행도 (0 ~ 100)
	UPROPERTY(VisibleAnywhere, Category = "Rotation")
	float CurrentProgress = 0.f;

	// 진행도에 따라 회전값을 갱신
	UFUNCTION(BlueprintCallable)
	void OnProgressUpdate_Rot(float NewProgress);

	// 헤더에서 선언
	FRotator TargetRotation;  // 목표 회전값
};
