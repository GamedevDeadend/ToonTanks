// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnBase.h"
#include"ToonTanks/Actors/Projectilebase.h"
#include "ToonTanks/Components/HealthComp.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComp>(TEXT("Health Component"));
}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	FVector LookatXY =  FVector( LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = FVector(TurretMesh->GetComponentLocation());

	FRotator TurretRotation = FVector(LookatXY - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
	
}

void APawnBase::Fire()
{
	if(FiredProjectile)
	{
		FVector PLocation = ProjectileSpawnPoint->GetComponentLocation(); 
		FRotator PRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* Temp = GetWorld()->SpawnActor<AProjectileBase>(FiredProjectile, PLocation, PRotation);
		Temp->SetOwner(this);
	}	
}

void APawnBase::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, BlastParticles, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DestructionSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ExplodeShake);

}




