#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "BacteriaBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerAttacked, ABacteriaBase*, Attacker);

UCLASS()
class VR_PRACTICE_API ABacteriaBase : public AActor
{
    GENERATED_BODY()

public:
    ABacteriaBase();

    virtual void Tick(float DeltaTime) override;
    virtual void OnDeath() {};

    // ����: BacteriaBase.h
    UFUNCTION(BlueprintCallable, Category = "Bacteria")
    virtual void TakeDamageBac();

    bool bShieldAnim = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
    bool Shield = false;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerAttacked OnPlayerAttacked;

    // ���ݷ�
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float AttackPower = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bacteria")
    UStaticMeshComponent* ShieldMesh;

    float getHealth();

protected:
    virtual void BeginPlay() override;
    virtual void Destroyed() override;

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
    float TrackingSpeed = 0.8f;

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
