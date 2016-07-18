// Copyright Lone Wolfe Gaming - Kyle Wolfe

#include "BattleTank.h"
#include "TankAimingComponent.h"
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

		// TODO fix firing
		//ControlledTank->Fire();
	}
}
