// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPwidget.generated.h"

/**
 * 
 */
UCLASS()
class CHICAHEROS_API UHPwidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (Bindwidget))
	class UProgressBar* HealthBar;

	void UpdateHealthPercent(float HealthPercent);
};
