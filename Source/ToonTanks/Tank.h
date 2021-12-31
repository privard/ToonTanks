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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 200;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UCameraComponent* Camera = nullptr;

	class AToonTanksPlayerController* PlayerController = nullptr;

	void Move(float Value);

	void Turn(float Value);
};
