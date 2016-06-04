// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* myPawn = GetControlledTank();

	if (!myPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Controller Found"));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank())
	{
		FVector HitLocation; // out parameter

		if (GetSightRayHitLocation(HitLocation)) // has "side-effect", going to line trace
		{
			UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
			// TODO tell control tank to aim at this point
		}
	}
}

// Get World Location through crosshair (linetrace), returns true if landscape hit
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(1.0);
	return true;
}