// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDwidget.generated.h"

/**
 * 
 */
UCLASS()

class CHICAHEROS_API UHUDwidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateHealthPercent(float HealthPercent);

protected:
	UPROPERTY(meta = (Bindwidget))
	class UProgressBar* HealthBar;
};
