// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "particle trail", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleTrail;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent *ProjectileMovement;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *ProjectileMesh;

	UPROPERTY( EditDefaultsOnly , Category = "Damage")
	TSubclassOf<UDamageType> DamnageType;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShakeBase> HitShake;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Move", meta = (AllowPrivateAccess = "true"))
	float ProjectileVelocity = 1300.0f;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float ProjectileDamage = 50.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
