// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* myPawn = GetControlledTank();

	if (myPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play: %s"), *myPawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No AI Controller Found"));
	}

	ATank* playerControlledTank = GetPlayerTank();

	if (playerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Found Player Tank: %s"), *playerControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Tank Found"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	return playerTank;
}


