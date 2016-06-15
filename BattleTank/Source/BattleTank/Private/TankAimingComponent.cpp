// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float launchSpeed)
{
	if (Barrel)
	{
		FVector OutLaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName ("BarrelTip"));

		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity (
			this,													
			OutLaunchVelocity,									
			StartLocation,										
			HitLocation,										
			launchSpeed,										
			false,													
			0.0f,												
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace		// parameter must be present to prevent bug
			// TODO report bug
		);

		if (bHaveAimSolution)
		{
			FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
			Barrel->MoveTo(AimDirection.Rotation().Pitch);
		}
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

