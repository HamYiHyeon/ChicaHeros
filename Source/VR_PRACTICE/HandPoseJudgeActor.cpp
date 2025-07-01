#include "HandPoseJudgeActor.h"
#include "Spawn_Spline.h"
#include "Components/SkeletalMeshComponent.h"
#include "PhysicsEngine/BodyInstance.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Pawn.h"

AHandPoseJudgeActor::AHandPoseJudgeActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHandPoseJudgeActor::BeginPlay()
{
	Super::BeginPlay();

	// ✅ VRPawn의 HandLeft 메시 자동 할당 (IsPlayerControlled 제거)
	for (TActorIterator<APawn> It(GetWorld()); It; ++It)
	{
		TArray<USkeletalMeshComponent*> Meshes;
		It->GetComponents(Meshes);

		for (auto* Mesh : Meshes)
		{
			if (Mesh && Mesh->GetName().Contains(TEXT("HandLeft")))
			{
				VRHandMesh = Mesh;
				UE_LOG(LogTemp, Warning, TEXT("✅ VRHandMesh 자동 할당됨: %s"), *VRHandMesh->GetName());
				break;
			}
		}

		if (VRHandMesh) break; // 첫 번째 발견한 핸드 메시로 설정
	}

	// ✅ Spawn_Spline_L 액터 자동 할당 (GetActorLabel 사용)
	for (TActorIterator<ASpawn_Spline> It(GetWorld()); It; ++It)
	{
		if (It->GetActorLabel().Contains(TEXT("MySpawn_Spline_L")))
		{
			SpawnedSplineActor = *It;
			UE_LOG(LogTemp, Warning, TEXT("✅ SpawnedSplineActor 자동 할당됨: %s"), *SpawnedSplineActor->GetName());
			break;
		}
	}
}

void AHandPoseJudgeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CompareHandsAndUpdateProgress();
}

void AHandPoseJudgeActor::CompareHandsAndUpdateProgress()
{
	if (!VRHandMesh || !SpawnedSplineActor)
	{
		UE_LOG(LogTemp, Error, TEXT("❌ VRHandMesh 또는 SpawnedSplineActor 미할당"));
		return;
	}

	// 🔍 최근 Spawn된 메시 찾기
	USkeletalMeshComponent* SpawnedMesh = nullptr;
	for (const auto& Tooth : SpawnedSplineActor->SpawnedTeeth)
	{
		if (Tooth.Actor && Tooth.MeshComp)
		{
			SpawnedMesh = Tooth.MeshComp;
			break;
		}
	}


	if (!SpawnedMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("❌ SpawnedMesh 찾을 수 없음"));
		return;
	}

	// ✅ 비교
	if (AreHandsMatching())
	{
		Progress = FMath::Clamp(Progress + 0.1f, 0.f, 1.f);
		UE_LOG(LogTemp, Warning, TEXT("✅ 손 포즈 일치! 진행도: %.2f"), Progress);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("❌ 손 포즈 불일치"));
	}
}

FBodyInstance* AHandPoseJudgeActor::GetBodyInstance(USkeletalMeshComponent* Mesh, const FName& BoneName)
{
	return Mesh ? Mesh->GetBodyInstance(BoneName) : nullptr;
}

bool AHandPoseJudgeActor::AreHandsMatching()
{
	USkeletalMeshComponent* SpawnedMesh = nullptr;
	for (const auto& Tooth : SpawnedSplineActor->SpawnedTeeth)
	{
		if (Tooth.Actor && Tooth.MeshComp)
		{
			SpawnedMesh = Tooth.MeshComp;
			break;
		}
	}

	if (!VRHandMesh || !SpawnedMesh) return false;

	bool bAllMatched = true;

	for (const FName& Bone : BoneNamesToCompare)
	{
		FBodyInstance* VRBody = GetBodyInstance(VRHandMesh, Bone);
		FBodyInstance* SpawnedBody = GetBodyInstance(SpawnedMesh, Bone);

		if (!VRBody || !SpawnedBody)
		{
			UE_LOG(LogTemp, Warning, TEXT("⚠️ 바디 인스턴스 없음: %s"), *Bone.ToString());
			bAllMatched = false;
			continue;
		}

		FTransform VRTransform = VRBody->GetUnrealWorldTransform();
		FTransform SpawnedTransform = SpawnedBody->GetUnrealWorldTransform();

		// 🔍 디버그 구체로 위치 표시
		DrawDebugSphere(GetWorld(), VRTransform.GetLocation(), 2.f, 8, FColor::Green, false, 0.05f);
		DrawDebugSphere(GetWorld(), SpawnedTransform.GetLocation(), 2.f, 8, FColor::Red, false, 0.05f);

		float PosDiff = FVector::Dist(VRTransform.GetLocation(), SpawnedTransform.GetLocation());
		float RotDiff = VRTransform.GetRotation().AngularDistance(SpawnedTransform.GetRotation()) * (180.f / PI);

		UE_LOG(LogTemp, Log, TEXT("🦴 Bone: %s | PosDiff: %.2f | RotDiff: %.2f"), *Bone.ToString(), PosDiff, RotDiff);

		if (PosDiff > PositionTolerance || RotDiff > RotationTolerance)
		{
			UE_LOG(LogTemp, Warning, TEXT("❌ 불일치: %s | Pos: %.2f | Rot: %.2f"), *Bone.ToString(), PosDiff, RotDiff);
			bAllMatched = false;
		}
	}

	return bAllMatched;
}

