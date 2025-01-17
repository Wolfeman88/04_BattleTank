// Copyright Lone Wolfe Gaming - Kyle Wolfe

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)/*, hidecategories(Collision)*/)
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void MoveTo(float);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesElevation = 40;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinDegreesElevation = 0;
};
