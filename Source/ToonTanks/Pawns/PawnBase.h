// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComp;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:

// COMPONENTS

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY (EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> FiredProjectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComp* HealthComponent;

//VARIABLES

	UPROPERTY(EditAnywhere, Category = "Destruction Sound")
	USoundBase* DestructionSound;

	UPROPERTY(EditAnywhere, Category = "Particle Effects");
	UParticleSystem* BlastParticles;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShakeBase> ExplodeShake;



public:
	// Sets default values for this pawn's properties
	APawnBase();
	virtual void HandleDestruction();

protected:

	void RotateTurret(FVector LookAtTarget);
	void Fire();

};
