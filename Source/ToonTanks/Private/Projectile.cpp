// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = Mesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->MaxSpeed = 1300.0f;
	MovementComponent->InitialSpeed = MovementComponent->MaxSpeed;

	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle"));
	TrailParticle->SetupAttachment(Mesh);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (IsValid(LaunchSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (IsValid(GetOwner()) && IsValid(OtherActor) && GetOwner() != OtherActor && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
		
		if (IsValid(HitParticle))
		{
			UGameplayStatics::SpawnEmitterAtLocation(this,  HitParticle, GetActorLocation(), GetActorRotation());
		}
		
		if (IsValid(HitSound))
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

		if (IsValid(HitCameraShake))
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
		}
	}
	
	Destroy();
}