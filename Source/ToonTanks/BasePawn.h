// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	// Forward declaration syntax to remove obligation to 
	// include CapsuleComponent.h in our header file.
	class UCapsuleComponent* CapsuleComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UStaticMeshComponent* TurretMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	USceneComponent* ProjectileSpawnPoint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UParticleSystem* ExplosionParticles = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class ABaseProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundBase* ExplosionSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

	void Fire();
	void Explode();
	void RotateTurret(FVector LookAtTarget);
};
