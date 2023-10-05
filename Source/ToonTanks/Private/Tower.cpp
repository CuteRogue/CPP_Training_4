// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TryFire();
}

bool ATower::InFireRange() const
{
	if (!IsValid(Tank))
	{ return false; }
	
	const FVector TargetVector = Tank->GetActorLocation() - GetActorLocation();
	const FVector TargetDirection = TargetVector.GetSafeNormal();
	const FVector FireRangeVector = GetActorLocation() + TargetDirection * FireRange;
	
	FHitResult HitResult;
	return GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), FireRangeVector, ECC_Pawn) && HitResult.GetActor() == Tank;
}

bool ATower::InFiringLine() const
{
	if (!IsValid(Tank))
	{ return false; }
	
	const FVector FireDirectionVector = GetActorLocation() + TurretMesh->GetForwardVector() *  FireRange;
	
	FHitResult HitResult;
	return GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), FireDirectionVector, ECC_Pawn) && HitResult.GetActor() == Tank;
}

void ATower::StartFiring()
{
	if (!IsFiring)
	{
		IsFiring = true;
		GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::TryFireAtTank, FireRate, true, 0);
	}
}

void ATower::StopFiring()
{
	if (IsFiring)
	{
		GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
		IsFiring = false;
	}
}

void ATower::TryFire(const bool DrawDebug)
{
	if (!IsValid(Tank) || !Tank->bIsAlive)
	{ return; }
	
	if (DrawDebug)
	{ DrawDebugTick(); }
	
	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
		
		if (InFiringLine())
		{
			StartFiring();
		}
	}
}

void ATower::TryFireAtTank()
{
	if (!IsValid(Tank) || !Tank->bIsAlive)
	{
		StopFiring();
		return;
	}

	if (InFiringLine())
	{
		Fire();
	}
	else
	{
		StopFiring();
	}
}

void ATower::Die()
{
	Super::Die();
	Destroy();
}

// Debug Area
void ATower::DrawDebugTick() const
{
	const FVector TargetVector = Tank->GetActorLocation() - GetActorLocation();
	const FVector TargetDirection = TargetVector.GetSafeNormal();
	const FVector FireRangeVector = GetActorLocation() + TargetDirection * FireRange;
	const FVector FireDirectionVector = GetActorLocation() + TurretMesh->GetForwardVector() *  FireRange;
		
	DrawDebugLine(GetWorld(), GetActorLocation(), FireRangeVector, FColor::Green);
	DrawDebugLine(GetWorld(), GetActorLocation(), FireDirectionVector, FColor::Red);
}