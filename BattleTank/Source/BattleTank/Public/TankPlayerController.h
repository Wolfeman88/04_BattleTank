// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// must be last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;

	// start tank moving barrel so shot would hit where crosshair intersects the world
	void AimTowardsCrosshair();

	// return OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	// return OUT parameter, true if success
	bool GetLookDirection(FVector2D ScreenLoc, FVector& LookDirection) const;

	// horizontal percentage location of the crosshair (left edge is 0)
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;

	// vertical percentage location of the crosshair (top edge is 0)
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333f;

	// distance searched for something to hit by aiming functions
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;
};