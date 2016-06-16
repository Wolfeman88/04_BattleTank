// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories(Collision))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void MoveTo(float);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 5;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesElevation = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinDegreesElevation = 0;
};
