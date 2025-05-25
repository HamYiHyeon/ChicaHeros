// Fill out your copyright notice in the Description page of Project Settings.


#include "HPwidget.h"
#include "Components/ProgressBar.h"

void UHPwidget::UpdateHealthPercent(float HealthPercent) {
	HealthBar->SetPercent(HealthPercent);
}