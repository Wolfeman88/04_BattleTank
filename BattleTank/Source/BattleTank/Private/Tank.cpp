// Copyright Lone Wolfe Gaming - Kyle Wolfe

#include "BattleTank.h"
#include "Tank.h"

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	auto ActualDamage = FMath::Min(CurrentHealth, DamagePoints);

	CurrentHealth -= ActualDamage;

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return ActualDamage;
}
