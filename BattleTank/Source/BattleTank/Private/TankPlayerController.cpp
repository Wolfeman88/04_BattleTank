// Copyright Lone Wolfe Gaming - Kyle Wolfe

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetPawn())
	{
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

		if (ensure(AimingComponent))
		{
			FVector HitLocation; // out parameter

			bool bGotHitLocation = GetSightRayHitLocation(HitLocation);

			if (bGotHitLocation) // has "side-effect", going to line trace
			{
				AimingComponent->AimAt(HitLocation);
			}
		}
	}
}

// Get World Location through crosshair (linetrace), returns true if landscape hit
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	// de-project the screen position of the crosshair to world direction
	FVector WorldDirection;
	bool bReturnValue = false;
	
	if (GetLookDirection(ScreenLocation, WorldDirection))
	{
		bReturnValue = GetLookVectorHitLocation(WorldDirection, HitLocation);
	}

	return bReturnValue;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	bool Check = false;

	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	// line trace succeeds
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		Check = true;
	}
	else
	{
		HitLocation = FVector::ZeroVector;
	}

	return Check;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLoc, FVector& LookDirection) const
{
	FVector CameraWorldLocation;	// to be discarded
	return DeprojectScreenPositionToWorld(ScreenLoc.X, ScreenLoc.Y, CameraWorldLocation, LookDirection);
}
