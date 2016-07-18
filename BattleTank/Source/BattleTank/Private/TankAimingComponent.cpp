// Copyright Lone Wolfe Gaming - Kyle Wolfe

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
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

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (ensure(Barrel))
	{
		FVector OutLaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName ("BarrelTip"));

		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity (
			this,													
			OutLaunchVelocity,									
			StartLocation,										
			HitLocation,										
			LaunchSpeed,										
			false,													
			0.0f,												
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace	
		);

		if (bHaveAimSolution)
		{
			FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

			if (ensure(Barrel) && ensure(Turret))
			{
				Barrel->MoveTo(AimDirection.Rotation().Pitch);
				Turret->MoveTo(AimDirection.Rotation().Yaw);
			}
		}
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (ensure(Barrel && ProjectileBlueprint))
	{
		if (isReloaded)
		{
			// initialize position and rotation of projectile to be spawned
			FVector BarrelTip = Barrel->GetSocketLocation(FName("BarrelTip"));
			FRotator BarrelDirection = Barrel->GetSocketRotation(FName("BarrelTip"));

			// spawn a projectile at the socket location
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, BarrelTip, BarrelDirection);

			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
		}
	}
}
