// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("AToonTanksGameMode::BeginPlay: Failed to init PlayerController"));
	}

	HandleGameStart();
}

void AToonTanksGameMode::HandleActorDied(AActor* DeadActor)
{
	if (ATank* Tank = Cast<ATank>(DeadActor))
	{
		Tank->HandleDestruction();
		EndGame(false);
	}
	else if (ATower* Tower = Cast<ATower>(DeadActor))
	{
		Tower->HandleDestruction();

		TArray<AActor*> RemainingTowers;
		UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), RemainingTowers);

		int32 nRemainingTowers = RemainingTowers.Num();
		UE_LOG(LogTemp, Warning, TEXT("Tower destroyed! %i towers remaining."), nRemainingTowers);
		
		if (nRemainingTowers <= 0)
		{
			EndGame(true);
		}
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	StartGame();
	if (PlayerController)
	{
		PlayerController->SetPlayerEnabledState(false);
		
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(PlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}
