// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float launchSpeed)
{
	if (Barrel)
	{
		FVector OutLaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName ("BarrelTip"));

		bool check = UGameplayStatics::SuggestProjectileVelocity (
			this,														// world context object
			OutLaunchVelocity,											// out parameter for launch direction
			StartLocation,												// start location of the projectile
			HitLocation,												// end location of the projectile
			launchSpeed,												// initial speed of the projectile
			false,														// prefer hight path flag
			0.0f,														// projectile size
			0.0f,														// override gravity
			ESuggestProjVelocityTraceOption::DoNotTrace					// dictating how to trace the path
		);

		if (check)
		{
			FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
			UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetOwner()->GetName(),  *AimDirection.ToString());
		}
	}
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

