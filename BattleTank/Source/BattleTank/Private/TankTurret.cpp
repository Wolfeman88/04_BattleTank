// Copyright Lone Wolfe Gaming - Kyle Wolfe

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::MoveTo(float Yaw)
{
	// clamping and scaling the (target - previous) turret rotation to maximum rotation speed
	float RotationChange = FMath::Clamp(Yaw, -MaxDegreesPerSecond, MaxDegreesPerSecond);
	RotationChange *= GetWorld()->DeltaTimeSeconds;
	
	// update the new pitch target rotation
	float Rotation = RelativeRotation.Yaw + RotationChange; 

	// rotating the barrel to the new target rotation
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
