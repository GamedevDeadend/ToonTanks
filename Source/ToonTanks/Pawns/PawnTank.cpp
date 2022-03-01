// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnTank.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"


APawnTank :: APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

bool APawnTank::CheckPlayerAlive()
{
	return bIsPlayerAlive;
}


// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

	if(PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector TraceHitLocation  = TraceHitResult.ImpactPoint;

		RotateTurret(TraceHitLocation); 
	}

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank :: CalculateMovement);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank :: CalculateRotation);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank :: Fire);

}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	 bIsPlayerAlive = false;

	 SetActorHiddenInGame(true);
	 SetActorTickEnabled(false);

	// HidePlayer.TODO Handle This Feature
}


void APawnTank::CalculateMovement(float value)
{
	MoveDirection = FVector(value * MoveSpeed * GetWorld()->DeltaTimeSeconds,0,0);
	// UE_LOG(LogTemp, Warning, TEXT("button is pressed"));
	
}

void APawnTank::CalculateRotation(float value)
{
	float RotationAmount = value* TurnSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotationAmount ,0);
	RotationDirection = FQuat(Rotation);
	
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}
