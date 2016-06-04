// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* myPawn = GetControlledTank();

	if (myPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play: %s"), *myPawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Controller Found"));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
