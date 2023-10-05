// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Base")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Base")
	class UProjectileMovementComponent* MovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Base")
	UParticleSystemComponent* TrailParticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category="SFX/VFX")
	UParticleSystem* HitParticle;
	UPROPERTY(EditDefaultsOnly, Category="SFX/VFX")
	USoundBase* LaunchSound;
	UPROPERTY(EditDefaultsOnly, Category="SFX/VFX")
	USoundBase* HitSound;
	UPROPERTY(EditDefaultsOnly, Category="SFX/VFX")
	TSubclassOf<UCameraShakeBase> HitCameraShake;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);
};
