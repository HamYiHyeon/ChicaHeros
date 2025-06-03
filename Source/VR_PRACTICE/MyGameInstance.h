// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VR_PRACTICE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	UPROPERTY(BlueprintReadWrite)
	bool bStageCleared = false;

	UPROPERTY(BlueprintReadWrite)
	bool GameStart = false;

	UPROPERTY(BlueprintReadWrite)
	int MaxWeaponIndex = 0;

	UPROPERTY(BlueprintReadWrite)
	TArray<bool> UnlockWeapon;

	UPROPERTY(BlueprintReadWrite)
	int Gold = 0;
};
