// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float FireRange = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float FireRate = 2.0f;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Fire")
	bool InFireRange() const;
	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Fire")
	bool InFiringLine() const;

private:
	class ATank* Tank;
	FTimerHandle FireRateTimerHandle;
	bool IsFiring = false;
	
	void DrawDebugTick() const;
	void StartFiring();
	void StopFiring();
	void TryFire(bool DrawDebug = false);
	void TryFireAtTank();

public:
	virtual void Die() override;
};
