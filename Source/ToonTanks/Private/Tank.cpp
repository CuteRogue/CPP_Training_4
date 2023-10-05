// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
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

	PlayerController = Cast<APlayerController>(GetController());

}

void ATank::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TryAimTurret();
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Rotate);
	
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(const float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Rotate(const float Value)
{
	FRotator DeltaRotator = FRotator::ZeroRotator;
	DeltaRotator.Yaw = Value * RotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotator, true);
}

void ATank::TryAimTurret(const bool DrawDebug) const
{
	if (!IsValid(PlayerController))
	{ return; }
	
	FHitResult HitResult;
	if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		if (DrawDebug)
		{ DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red); }
		
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::Die()
{
	Super::Die();
	
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	bIsAlive = false;
}

APlayerController* ATank::GetPlayerController() const
{
	return PlayerController;
}
