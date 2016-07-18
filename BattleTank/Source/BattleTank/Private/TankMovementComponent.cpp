// Copyright Lone Wolfe Gaming - Kyle Wolfe

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector AITankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float AIForwardThrow = FVector::DotProduct(AITankForward, AIForwardIntention);
	IntendMoveForward(AIForwardThrow);

	float AITurnThrow = FVector::CrossProduct(AITankForward, AIForwardIntention).Z;
	IntendTurnRight(AITurnThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (ensure(LeftTrack && RightTrack))
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (ensure(LeftTrack && RightTrack))
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	}
}