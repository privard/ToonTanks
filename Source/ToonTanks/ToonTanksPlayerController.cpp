// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		UE_LOG(LogTemp, Warning, TEXT("AToonTanksPlayerController::SetPlayerEnabledState: Enabling Player Input"));
		GetPawn()->EnableInput(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AToonTanksPlayerController::SetPlayerEnabledState: Disabling Player Input"));
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}