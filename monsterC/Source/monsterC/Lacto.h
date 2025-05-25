// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BacteriaBase.h"
#include "Lacto.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERC_API ALacto : public ABacteriaBase
{
	GENERATED_BODY()
	
public:
	ALacto();

protected:
	virtual void Tick(float DeltaTime) override;
};
