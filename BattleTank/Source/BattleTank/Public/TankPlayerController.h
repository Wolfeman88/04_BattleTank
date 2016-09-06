// Copyright Lone Wolfe Gaming - Kyle Wolfe

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// must be last include

class UTankAimingComponent;

/**
 * responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

private:
	// start tank moving barrel so shot would hit where crosshair intersects the world
	void AimTowardsCrosshair();

	// return OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector&) const;

	bool GetLookVectorHitLocation(FVector, FVector&) const;

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

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();
};
