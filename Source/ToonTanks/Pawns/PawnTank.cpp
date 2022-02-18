// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"


APawnTank :: APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}


// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank :: CalculateMovement);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank :: CalculateRotation);

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