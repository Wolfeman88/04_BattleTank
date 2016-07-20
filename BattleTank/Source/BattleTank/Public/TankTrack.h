// Copyright Lone Wolfe Gaming - Kyle Wolfe

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// sets throttle between -1 to +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	// max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000;	// assume 40 ton tank and 1g acceleration

private:
	UTankTrack();
	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	const float ONE_HALF = 0.5f;

	float CurrentThrottle = 0;
	void DriveTrack();
};
