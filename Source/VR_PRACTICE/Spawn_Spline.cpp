#include "Spawn_Spline.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

ASpawn_Spline::ASpawn_Spline()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Root);

}

void ASpawn_Spline::BeginPlay()
{
	Super::BeginPlay();

	// ⭐ 첫 메시 즉시 Spawn
	SpawnHand();

	// 초기화
	SpawnTimer = 0.0f;
}

void ASpawn_Spline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnTimer += DeltaTime;
	if (SpawnTimer >= SpawnInterval)
	{
		SpawnTimer = 0.0f;
		SpawnHand();
	}

	for (FMovingTooth& Tooth : SpawnedTeeth)
	{
		if (!Tooth.Actor) continue;

		Tooth.ElapsedTime += DeltaTime;
		float Distance = Tooth.ElapsedTime * MoveSpeed;

		if (Distance >= MaxTravelDistance)
		{
			Tooth.Actor->Destroy();
			Tooth.Actor = nullptr;
			continue;
		}


		FVector StartLocation = Arrow->GetComponentLocation();
		FVector Direction = Tooth.InitialRotation.Vector(); // ✅ 회전에서 방향 추출
		FVector NewLocation = StartLocation + Direction * Distance;


		Tooth.Actor->SetActorLocation(NewLocation);
		//Tooth.Actor->SetActorRotation(Tooth.InitialRotation); // ✅ 고정된 회전 유지
	}

	// 정리
	SpawnedTeeth.RemoveAll([](const FMovingTooth& Tooth) { return Tooth.Actor == nullptr; });
}

void ASpawn_Spline::SpawnHand()
{
	if (!Target_L)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target_L Skeletal Mesh is not assigned!"));
		return;
	}

	FVector SpawnLocation = Arrow->GetComponentLocation();
	FRotator FixedDirection = Arrow->GetComponentRotation(); // ✅ 방향 저장

	FActorSpawnParameters Params;
	AActor* NewHand = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), SpawnLocation, FixedDirection, Params);

	if (NewHand)
	{
		// 메시 컴포넌트 생성
		USkeletalMeshComponent* SkeletalMeshComp = NewObject<USkeletalMeshComponent>(NewHand);
		if (SkeletalMeshComp)
		{
			SkeletalMeshComp->RegisterComponent();
			NewHand->AddInstanceComponent(SkeletalMeshComp); // ⭐ 추가

			SkeletalMeshComp->SetSkeletalMesh(Target_L);

			// 랜덤 회전 설정
			FRotator RandomMeshRotation = FRotator(
				FMath::FRandRange(-80.f, 80.f),
				FMath::FRandRange(0.f, 360.f),
				FMath::FRandRange(-45.f, 45.f)
			);
			SkeletalMeshComp->SetRelativeRotation(RandomMeshRotation);

			// 루트 처리
			if (!NewHand->GetRootComponent())
			{
				NewHand->SetRootComponent(SkeletalMeshComp);
			}
			else
			{
				SkeletalMeshComp->AttachToComponent(NewHand->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			}
			SkeletalMeshComp->SetRelativeLocation(FVector::ZeroVector);

			// 충돌 및 물리 설정
			SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			SkeletalMeshComp->SetCollisionObjectType(ECC_Pawn);
			SkeletalMeshComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
			SkeletalMeshComp->SetGenerateOverlapEvents(true);
			SkeletalMeshComp->SetNotifyRigidBodyCollision(true); // Hit 이벤트용
			//SkeletalMeshComp->SetSimulatePhysics(true);
			//SkeletalMeshComp->WakeAllRigidBodies(); // 바로 물리 활성화

		}

		// ✅ 구조체 생성 및 회전 저장
		FMovingTooth NewStruct;
		NewStruct.Actor = NewHand;
		NewStruct.MeshComp = SkeletalMeshComp; // 스켈레탈 메시 컴포넌트 저장(넘겨주기 위함)
		NewStruct.ElapsedTime = 0.0f;
		NewStruct.InitialRotation = FixedDirection; // ⭐ 방향 정보 저장


		SpawnedTeeth.Add(NewStruct);
	}
}



