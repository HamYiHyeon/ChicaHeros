// Fill out your copyright notice in the Description page of Project Settings.


#include "NanoRobot.h"
#include "MyGameInstance.h"

// Sets default values
ANanoRobot::ANanoRobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANanoRobot::BeginPlay()
{
	Super::BeginPlay();
    UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if(GI && !GI->GameStart) {
		GI->GameStart = true;
	}
	else {
		if (GI->bStageCleared) {
			StageCleared = 1;
		}
		else if (!GI->bStageCleared) {
			StageCleared = -1;
		}
		else StageCleared = 0;
	}
	DanceIndex = FMath::RandRange(0, 2);
}

// Called every frame
void ANanoRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

