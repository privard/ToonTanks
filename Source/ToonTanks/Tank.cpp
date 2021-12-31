// Fill out your copyright notice in the Descripttion page of Project Settings.

#include "Tank.h"

#include "ToonTanksPlayerController.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AToonTanksPlayerController>(GetController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("ATank::BeginPlay: Failed to initialize player controller."))
	}
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	Explode();
	if (PlayerController)
	{
		PlayerController->SetPlayerEnabledState(false);
		PlayerController->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset({ Value * DeltaSeconds * MovementSpeed, 0.f, 0.f }, true);
}

void ATank::Turn(float Value)
{
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation({ 0.f, Value * DeltaSeconds * TurnSpeed, 0.f }, true);
}