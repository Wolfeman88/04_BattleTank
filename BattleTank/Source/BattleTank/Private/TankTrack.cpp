// Copyright Lone Wolfe Gaming - Kyle Wolfe

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	FVector RVector = GetRightVector();

	// magnitude of tank velocity in the left/right direction, i.e. "slip"
	auto SlippageSpeed = FVector::DotProduct(RVector, GetComponentVelocity());

	// work-out required acceleration this frame to counter slippage, Speed / Time
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * RVector;

	// calculate sideways force
	auto TankBody = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankBody->GetMass() * CorrectionAcceleration) * ONE_HALF;

	// apply sideways force
	TankBody->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
