#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "BacteriaBase.generated.h"

UCLASS()
class VR_PRACTICE_API ABacteriaBase : public AActor
{
    GENERATED_BODY()

public:
    ABacteriaBase();

    virtual void Tick(float DeltaTime) override;

    // ������ �Դ� �Լ�
    virtual float TakeDamage(float DamageAmount);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
    float Shield = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
    float MaxShield = 50.f;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float Wait;
    float WaitTime = 1.5f;
    // ü��
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float Health;

    // �̵� �ӵ�
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float MoveSpeed;

    // �ִ� �̵� �ӵ�
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float MaxSpeed;
    float IncSpeed = 5.f;

    // ȸ�� �ӵ�
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float TrackingSpeed = 1.5f;

    // ���ݷ�
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float AttackPower = 10.f;

    // ���� ����
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float AttackRange = 200.f;

    // �޽� ������Ʈ
    UPROPERTY(VisibleAnywhere, Category = "Bacteria")
    UStaticMeshComponent* MeshComponent;

    // �÷��̾� ����
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    APawn* PlayerPawn;

    UPROPERTY(VisibleAnywhere, Category = "Bacteria")
    float Distance;

    // �÷��̾� ����
    UPROPERTY()
    UCameraComponent* CameraComp;

    // �÷��̾� ��ġ ĳ��
    FVector PlayerLocation;
};
