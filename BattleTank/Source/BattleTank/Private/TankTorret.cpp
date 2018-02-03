// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTorret.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

void UTankTorret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto AzimuthChange = RelativeSpeed * DegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto YawNewRotation = RelativeRotation.Yaw + AzimuthChange;

	SetRelativeRotation(FRotator(0, YawNewRotation, 0));
}

