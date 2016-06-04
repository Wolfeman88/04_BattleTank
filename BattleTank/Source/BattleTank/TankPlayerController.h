// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	ATank* GetControlledTank() const;

	// start tank moving barrel so shot would hit where crosshair intersects the world
	void AimTowardsCrosshair();

	// return OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	// horizontal percentage location of the crosshair (left edge is 0)
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	// vertical percentage location of the crosshair (top edge is 0)
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;
};
