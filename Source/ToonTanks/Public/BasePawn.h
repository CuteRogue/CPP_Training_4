// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Base")
	class UCapsuleComponent* CapsuleCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Base")
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Base")
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Base")
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Base")
	class UArrowComponent* ProjectileSpawnDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Base")
	class UHealthComponent* Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Turret")
	float TurretRotateSpeed = 10.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Projectile")
	TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, Category="SFX/VFX")
	UParticleSystem* DeathParticle;
	UPROPERTY(EditDefaultsOnly, Category="SFX/VFX")
	USoundBase* DeathSound;
	UPROPERTY(EditDefaultsOnly, Category="SFX/VFX")
	TSubclassOf<UCameraShakeBase> DeathCameraShake;

	void RotateTurret(const FVector& LookTarget) const;
	void Fire();

public:
	virtual void Die();
};
