// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	APlayerController* PlayerController;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank")
	float RotateSpeed;

	void Move(float Value);
	void Rotate(float Value);
	void TryAimTurret(bool DrawDebug = false) const;

public:
	bool bIsAlive = true;
	
	virtual void Die() override;
	APlayerController* GetPlayerController() const;
};
