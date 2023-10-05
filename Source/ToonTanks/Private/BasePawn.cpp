// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "HealthComponent.h"
#include "Projectile.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleCollider;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleCollider);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	ProjectileSpawnDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Projectile Spawn Direction"));
	ProjectileSpawnDirection->SetupAttachment((ProjectileSpawnPoint));

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ABasePawn::RotateTurret(const FVector& LookTarget) const
{
	const FVector TargetVector = LookTarget - TurretMesh->GetComponentLocation();
	const FRotator TargetRotation = FRotator(TurretMesh->GetComponentRotation().Pitch, TargetVector.Rotation().Yaw, TurretMesh->GetComponentRotation().Roll);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			TargetRotation,
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
			TurretRotateSpeed
		)
	);
}

void ABasePawn::Fire()
{
	const auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	SpawnedProjectile->SetOwner(this);
}

void ABasePawn::Die()
{
	if (IsValid(DeathParticle))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}

	if (IsValid(DeathSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	if (IsValid(DeathCameraShake))
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);
	}
}

