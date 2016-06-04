// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* myPawn = GetControlledTank();

	if (!myPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("No AI Controller Found"));
	}

	ATank* playerControlledTank = GetPlayerTank();

	if (!playerControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Tank Found"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	// don't need to protect pointer, failed cast gets NULL
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	// don't need to protect pointer, failed cast gets NULL
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


