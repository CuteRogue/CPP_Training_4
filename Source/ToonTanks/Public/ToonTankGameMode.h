// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;
	class AToonTankPlayerController* PlayerController;
	FTimerHandle CountDownTimerHandle;

	bool IsGameStarted = false;
	float StartDelay = 2.0f;
	int32 Delay = 0;
	int32 TargetTowers = 0;

	void GameStart();
	void CountDownUpdate();
	int32 GetTargetTowersCount() const;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bIsWin);
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetRemainingDelay() const;
	
	void ActorDied(AActor* DeadActor);
};
