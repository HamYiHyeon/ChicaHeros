// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BacteriaBase.h"
#include "Mutans.generated.h"

/**
 *
 */
UCLASS()
class MONSTERC_API AMutans : public ABacteriaBase
{
	GENERATED_BODY()

public:
	AMutans();

protected:
	virtual void Tick(float DeltaTime) override;
};