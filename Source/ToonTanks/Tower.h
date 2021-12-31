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

public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Attack")
	float FireRange = 300.f;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float FireRate = 2.f;

	class ATank* Tank = nullptr;
	
	FTimerHandle FireRateTimerHandle;

	void CheckFireConditions();
	bool isTankInRange();
};
