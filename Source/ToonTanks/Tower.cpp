// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isTankInRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

bool ATower::isTankInRange()
{
	if (!Tank || Tank->IsHidden()) { return false; }

	float DistanceToTank = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
	if (DistanceToTank <= FireRange) { return true; }
	return false;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Explode();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!Tank) {
		UE_LOG(LogTemp, Error, TEXT("Tank Pawn not found"));
	}

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireConditions, FireRate, true);
}

void ATower::CheckFireConditions()
{
	if (isTankInRange())
	{
		Fire();
	}
}
