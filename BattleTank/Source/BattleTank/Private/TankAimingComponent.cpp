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

void UTankAimingComponent::BeginPlay()
{
	// so that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (AmmoCounter <= 0)
	{
		FireStatus = EFiringStatus::OutOfAmmo;
	}
	else if (FPlatformTime::Seconds() < (LastFireTime + ReloadTimeInSeconds))
	{
		FireStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FireStatus = EFiringStatus::Aiming;
	}
	else
	{
		FireStatus = EFiringStatus::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	bool bCheck = false;

	if (ensure(Barrel))
	{
		FVector ForwardVector = Barrel->GetForwardVector();
		bCheck = !ForwardVector.Equals(AimDirection, BarrelMovingTolerance);
	}

	return bCheck;
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
			AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (ensure(Barrel && Turret))
	{
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotator = AimAsRotator - BarrelRotator;

		Barrel->MoveTo(DeltaRotator.Pitch);

		if (FMath::Abs(DeltaRotator.Yaw) < 180)
		{
			Turret->MoveTo(DeltaRotator.Yaw);
		}
		else
		{
			Turret->MoveTo(-DeltaRotator.Yaw);
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
	if ((FireStatus == EFiringStatus::Locked) || (FireStatus == EFiringStatus::Aiming))
	{
		if (ensure(Barrel && ProjectileBlueprint))
		{
			// initialize position and rotation of projectile to be spawned
			FVector BarrelTip = Barrel->GetSocketLocation(FName("BarrelTip"));
			FRotator BarrelDirection = Barrel->GetSocketRotation(FName("BarrelTip"));

			// spawn a projectile at the socket location
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, BarrelTip, BarrelDirection);

			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
			AmmoCounter--;
		}
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FireStatus;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return AmmoCounter;
}
