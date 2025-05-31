// Fill out your copyright notice in the Description page of Project Settings.


#include "car.h"

// Sets default values
Acar::Acar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Acar::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(8.f);
}

// Called every frame
void Acar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ForwardMove = GetActorForwardVector() * movespeed * DeltaTime;
	AddActorWorldOffset(ForwardMove, true);
}

