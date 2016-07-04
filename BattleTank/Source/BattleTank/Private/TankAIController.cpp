// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	myPawn = Cast<ATank>(GetPawn());;
	playerControlledTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if ((playerControlledTank) && (myPawn))
	{
		MoveToActor(playerControlledTank, AcceptanceRadius);	// TODO check radius is in cm

		FVector AimTarget = playerControlledTank->GetActorLocation();
		myPawn->AimAt(AimTarget);

		myPawn->Fire();		//TODO don't fire every frame
	}
}


