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

	// ȸ���� �޽� (�ڵ� �Ҵ� ���)
	UPROPERTY(EditAnywhere, Category = "Rotation")
	UStaticMeshComponent* RotateComp;

	// �ʱ� ȸ����
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator InitialRotation = FRotator::ZeroRotator;

	// �ִ� ȸ�� ������ (���൵ �߰����� �ִ�)
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator MaxRotationOffset = FRotator(0.f, 0.f, 50.f);

	// ȸ�� ���� �ӵ�
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationInterpSpeed = 5.f;

	// ���� ���൵ (0 ~ 100)
	UPROPERTY(VisibleAnywhere, Category = "Rotation")
	float CurrentProgress = 0.f;

	// ���൵�� ���� ȸ������ ����
	UFUNCTION(BlueprintCallable)
	void OnProgressUpdate_Rot(float NewProgress);

	// ������� ����
	FRotator TargetRotation;  // ��ǥ ȸ����
};
