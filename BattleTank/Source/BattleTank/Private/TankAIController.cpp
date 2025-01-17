// Copyright Lone Wolfe Gaming - Kyle Wolfe

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"
// depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto playerControlledTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (ensure(playerControlledTank && ControlledTank))
	{
		MoveToActor(playerControlledTank, AcceptanceRadius);	// TODO check radius is in cm
		FVector AimTarget = playerControlledTank->GetActorLocation();
		
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(AimTarget);

		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
		{
			AimingComponent->Fire();
		}
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (PossessedTank)
		{
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
		}
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (GetPawn())
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}
