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

    // 예시: BacteriaBase.h
    UFUNCTION(BlueprintCallable, Category = "Bacteria")
    virtual void TakeDamageBac();

    bool bShieldAnim = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
    bool Shield = false;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerAttacked OnPlayerAttacked;

    // 공격력
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float AttackPower = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bacteria")
    UStaticMeshComponent* ShieldMesh;

    float getHealth();

protected:
    virtual void BeginPlay() override;
    virtual void Destroyed() override;

    // 체력
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float Health;

    // 이동 속도
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float MoveSpeed;

    // 최대 이동 속도
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float MaxSpeed;
    float IncSpeed = 5.f;

    // 회전 속도
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float TrackingSpeed = 0.8f;

    // 공격 범위
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float AttackRange = 200.f;

    // 메시 컴포넌트
    UPROPERTY(VisibleAnywhere, Category = "Bacteria")
    UStaticMeshComponent* MeshComponent;

    // 플레이어 참조
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    APawn* PlayerPawn;

    UPROPERTY(VisibleAnywhere, Category = "Bacteria")
    float Distance;

    // 플레이어 참조
    UPROPERTY()
    UCameraComponent* CameraComp;

    // 플레이어 위치 캐시
    FVector PlayerLocation;
};
