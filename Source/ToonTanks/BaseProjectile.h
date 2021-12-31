#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class TOONTANKS_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	class UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float InitialSpeed = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MaxSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float BaseDamage = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	class UParticleSystemComponent* ProjectileParticles = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	class UParticleSystem* HitParticles = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundBase* LaunchSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundBase* HitSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* SourceComponent, AActor* TargetActor, UPrimitiveComponent* TargetComponent, FVector NormalImpulse, const FHitResult& Hit);	
};
