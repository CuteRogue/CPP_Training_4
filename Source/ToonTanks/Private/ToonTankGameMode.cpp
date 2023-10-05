// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"

#include "Tank.h"
#include "ToonTankPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameStart();
}

void AToonTankGameMode::GameStart()
{
	TargetTowers = GetTargetTowersCount();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (IsValid(PlayerController))
	{
		PlayerController->SetPlayerEnabledState(false);
	}

	Delay = FMath::CeilToInt32(StartDelay);
	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this, &AToonTankGameMode::CountDownUpdate, 1.0f, true);
}

void AToonTankGameMode::CountDownUpdate()
{
	Delay -= 1;
	
	if (Delay <= 0 && !IsGameStarted)
	{
		if (IsValid(PlayerController))
		{
			PlayerController->SetPlayerEnabledState(true);
			IsGameStarted = true;
		}
	}
	if (Delay <= -1)
	{
		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
	}
}

int32 AToonTankGameMode::GetTargetTowersCount() const
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}

int32 AToonTankGameMode::GetRemainingDelay() const
{
	return Delay;
}

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if (IsValid(Tank) && DeadActor == Tank)
	{
		Tank->Die();

		if (IsValid(Tank->GetPlayerController()))
		{
			PlayerController->SetPlayerEnabledState(false);
		}

		GameOver(false);
	}
	else if (ATower* DeadTower = Cast<ATower>(DeadActor))
	{
		DeadTower->Die();

		if (--TargetTowers <= 0)
		{
			GameOver(true);
		}
	}
}
