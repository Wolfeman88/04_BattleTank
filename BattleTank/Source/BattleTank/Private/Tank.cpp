// Copyright Lone Wolfe Gaming - Kyle Wolfe

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (ensure(Barrel))
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
