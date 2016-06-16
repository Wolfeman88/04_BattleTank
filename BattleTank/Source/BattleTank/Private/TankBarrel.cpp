// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::MoveTo(float Pitch)
{
	// clamping and scaling the (target - previous) barrel rotation to maximum rotation speed
	float ElevationChange = FMath::Clamp((Pitch - RelativeRotation.Pitch), -MaxDegreesPerSecond, MaxDegreesPerSecond);
	ElevationChange *= GetWorld()->DeltaTimeSeconds;

	// update and clamp the new pitch target rotation
	float RawNewPitch = RelativeRotation.Pitch + ElevationChange;
	RawNewPitch = FMath::Clamp(RawNewPitch, MinDegreesElevation, MaxDegreesElevation);

	// rotating the barrel to the new target rotation
	SetRelativeRotation(FRotator(RawNewPitch, 0, 0));
}


