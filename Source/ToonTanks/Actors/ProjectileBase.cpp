// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Actors/ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{return;}

	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, MyOwner->GetInstigatorController(), this, DamnageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		//UE_LOG(LogTemp, Warning, TEXT("Damage Applied to %s"), *OtherActor->GetName());
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitShake);
		Destroy();
	}
}

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = ProjectileVelocity;
	ProjectileMovement->MaxSpeed = ProjectileVelocity;
	
	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail"));
	ParticleTrail->SetupAttachment(RootComponent);
	InitialLifeSpan  = 3.0f; 	

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}



