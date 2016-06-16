// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::MoveTo(float Yaw)
{
	// clamping and scaling the (target - previous) turret rotation to maximum rotation speed
	float RotationChange = FMath::Clamp((ShiftRotation360(Yaw) - ShiftRotation360(RelativeRotation.Yaw)), -MaxDegreesPerSecond, MaxDegreesPerSecond);
	RotationChange *= GetWorld()->DeltaTimeSeconds;

	if (MaxDegreesPerSecond == 50)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), RotationChange);
	}
	
	// update the new pitch target rotation
	float RawNewPitch = RelativeRotation.Yaw + RotationChange;

	// rotating the barrel to the new target rotation
	SetRelativeRotation(FRotator(0, RawNewPitch, 0));
}

float UTankTurret::ShiftRotation360(float angle)
{
	return angle + 360;
}


