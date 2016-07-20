// Copyright Lone Wolfe Gaming - Kyle Wolfe

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	FVector RVector = GetRightVector();

	// magnitude of tank velocity in the left/right direction, i.e. "slip"
	auto SlippageSpeed = FVector::DotProduct(RVector, GetComponentVelocity());

	// work-out required acceleration this frame to counter slippage, Speed / Time
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * RVector;

	// calculate sideways force
	auto TankBody = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankBody->GetMass() * CorrectionAcceleration) * ONE_HALF;

	// apply sideways force
	TankBody->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>((CurrentThrottle + Throttle), -1, 1);
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}
