// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "BasePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksGameMode.h"
#include "Tower.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("UHealthComponent::BeginPlay: Failed to init GameMode"));
	}

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamage);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::OnDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) { 
		UE_LOG(LogTemp, Warning, TEXT("UHealthComponent::OnDamage: Event with 0 value on %s"), *DamagedActor->GetName());
		return; 
	}

	if (DamagedActor != GetOwner()) {
		UE_LOG(LogTemp, Error, TEXT("UHealthComponent::OnDamage: DamagedActor is not component owner"), *DamagedActor->GetName());
		return;
	}

	Health -= Damage;
	if (Health <= 0.f && DamagedActor && GameMode)
	{
		GameMode->HandleActorDied(DamagedActor);
	} 
}

