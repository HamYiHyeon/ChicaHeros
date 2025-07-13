#include "HandPoseJudgeActor.h"
#include "Spawn_Spline.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Pawn.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h" // 꼭 추가!

AHandPoseJudgeActor::AHandPoseJudgeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoneNamesToCompare_l = {
		FName("index_03_l"),
		FName("middle_03_l"),
		FName("ring_03_l"),
		FName("pinky_03_l"),
		FName("thumb_03_l"),
		FName("middle_metacarpal_l")
	};

	BoneNamesToCompare_r = {
		FName("index_03_r"),
		FName("middle_03_r"),
		FName("ring_03_r"),
		FName("pinky_03_r"),
		FName("thumb_03_r"),
		FName("middle_metacarpal_r")
	};
}

void AHandPoseJudgeActor::BeginPlay()
{
	Super::BeginPlay();

	// ✅ VRHandMesh 왼손/오른손 자동 할당
	for (TActorIterator<APawn> It(GetWorld()); It; ++It)
	{
		TArray<USkeletalMeshComponent*> Meshes;
		It->GetComponents(Meshes);

		for (auto* Mesh : Meshes)
		{
			if (Mesh)
			{
				if (Mesh->GetName().Contains(TEXT("HandLeft")))
				{
					VRHandMesh_L = Mesh;
					UE_LOG(LogTemp, Warning, TEXT("✅ 왼손 메시 할당됨: %s"), *Mesh->GetName());
				}
				else if (Mesh->GetName().Contains(TEXT("HandRight")))
				{
					VRHandMesh_R = Mesh;
					UE_LOG(LogTemp, Warning, TEXT("✅ 오른손 메시 할당됨: %s"), *Mesh->GetName());
				}
			}
		}
	}

	// ✅ SpawnSpline 자동 할당
	for (TActorIterator<ASpawn_Spline> It(GetWorld()); It; ++It)
	{
		const FString Label = It->GetActorLabel();

		if (Label.Contains(TEXT("MySpawn_Spline_L")))
		{
			SpawnedSplineActor_L = *It;
			UE_LOG(LogTemp, Warning, TEXT("✅ 왼손 SpawnedSplineActor 할당됨: %s"), *Label);
		}
		else if (Label.Contains(TEXT("MySpawn_Spline_R")))
		{
			SpawnedSplineActor_R = *It;
			UE_LOG(LogTemp, Warning, TEXT("✅ 오른손 SpawnedSplineActor 할당됨: %s"), *Label);
		}
	}

	//ProgressToothActor 찾기
	for (TActorIterator<AProgressToothActor> It(GetWorld()); It; ++It)
	{
		ToothProgressActor = *It;
		UE_LOG(LogTemp, Warning, TEXT("🦷 ToothProgressActor 할당됨: %s"), *ToothProgressActor->GetName());
		break;
	}

	//ProgressRotatingActor 찾기
	for (TActorIterator<AProgressRotatingActor> It(GetWorld()); It; ++It)
	{
		RotatingActor = *It;
		UE_LOG(LogTemp, Warning, TEXT("🦷 RotatingActor 할당됨: %s"), *RotatingActor->GetName());
		break;
	}

	//ProgressRotatingActor2 찾기
	for (TActorIterator<AProgressRotatingActor2> It(GetWorld()); It; ++It)
	{
		RotatingActor2 = *It;
		UE_LOG(LogTemp, Warning, TEXT("🦷 RotatingActor2 할당됨: %s"), *RotatingActor2->GetName());
		break;
	}

}

void AHandPoseJudgeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CompareHandsAndUpdateProgress();
}

void AHandPoseJudgeActor::CompareHandsAndUpdateProgress()
{
	if (!VRHandMesh_L || !VRHandMesh_R || !SpawnedSplineActor_L || !SpawnedSplineActor_R)
	{
		if (!Logonce)
		{
			UE_LOG(LogTemp, Error, TEXT("❌ 손 메시 또는 Spawn 액터 미할당"));
			Logonce = true;
		}
		return;
	}

	bool bAnyMatch = false;

	// ✋ 왼손/오른손 각각 비교
	struct FHandMatchConfig
	{
		FString Label;
		TArray<FName>& BoneList;
		ASpawn_Spline* SplineActor;
		USkeletalMeshComponent* HandMesh;
	};

	TArray<FHandMatchConfig> HandConfigs = {
		{ TEXT("왼손"), BoneNamesToCompare_l, SpawnedSplineActor_L, VRHandMesh_L },
		{ TEXT("오른손"), BoneNamesToCompare_r, SpawnedSplineActor_R, VRHandMesh_R }
	};

	for (FHandMatchConfig& Hand : HandConfigs)
	{
		for (int32 i = Hand.SplineActor->SpawnedTeeth.Num() - 1; i >= 0; --i)
		{
			FMovingTooth& Tooth = Hand.SplineActor->SpawnedTeeth[i];
			USkeletalMeshComponent* SpawnedMesh = Tooth.MeshComp;
			if (!SpawnedMesh || !Tooth.Actor) continue;

			// 📏 루트 거리 확인
			const float Dist = FVector::Dist(
				Hand.HandMesh->GetComponentLocation(),
				SpawnedMesh->GetComponentLocation());

			//UE_LOG(LogTemp, Log, TEXT("📏 [%s] 루트 거리: %.2f (허용: %.2f)"), *Hand.Label, Dist, MatchingDistanceThreshold);

			if (Dist > MatchingDistanceThreshold) continue;

			int32 MatchedCount = 0;

			for (const FName& Bone : Hand.BoneList)
			{
				const FTransform VRBoneWorld = Hand.HandMesh->GetSocketTransform(Bone, RTS_World);	// 피직스 에셋에 대한 월드 좌표계 기준 위치
				const FTransform SpawnedBoneWorld = SpawnedMesh->GetSocketTransform(Bone, RTS_World);

				const float PosDiff = FVector::Dist(VRBoneWorld.GetLocation(), SpawnedBoneWorld.GetLocation());
				const float RotDiff = VRBoneWorld.GetRotation().AngularDistance(SpawnedBoneWorld.GetRotation()) * (180.f / PI);

				/*UE_LOG(LogTemp, Log,
					TEXT("🔍 [%s] Bone: %s | PosDiff: %.2f | RotDiff: %.2f"),
					*Hand.Label, *Bone.ToString(), PosDiff, RotDiff);
					*/
				if (PosDiff <= PositionTolerance && RotDiff <= RotationTolerance)
				{
					MatchedCount++;
				}
			}

			//UE_LOG(LogTemp, Log, TEXT("📊 [%s] 매칭된 본 수: %d / %d"), *Hand.Label, MatchedCount, Hand.BoneList.Num());

			if (MatchedCount >= 4)
			{
				bAnyMatch = true;
				Progress += 5.0f;
				//UE_LOG(LogTemp, Warning, TEXT("🎉 [%s] 손 포즈 일치! 진행도: %.2f"), *Hand.Label, Progress);

				// 손 매칭 진행도 전달
				if (ToothProgressActor)
				{
					ToothProgressActor->OnProgressUpdated(Progress);
				}
				
				// 이번엔 회전해야 하는 액터에 진행도 전달
				if (RotatingActor)
				{
					RotatingActor->OnProgressUpdate_Rot(Progress);
				}

				if (RotatingActor2)
				{
					RotatingActor2->OnProgressUpdate_Rot(Progress);
				}

				// ✅ 파티클 이펙트 생성
				if (MatchingEffect)
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						GetWorld(),
						MatchingEffect,
						SpawnedMesh->GetComponentLocation(),
						FRotator::ZeroRotator
					);
				}

				Tooth.Actor->Destroy();
				Tooth.Actor = nullptr;
				Hand.SplineActor->SpawnedTeeth.RemoveAt(i);
				break;
			}
		}
	}

	if (!bAnyMatch)
	{
		//UE_LOG(LogTemp, Warning, TEXT("❌ 손 포즈 불일치 (가까운 손은 있었지만 포즈 미일치)"));
	}
}
