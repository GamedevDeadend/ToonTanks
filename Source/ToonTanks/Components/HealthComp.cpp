// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Components/HealthComp.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHealthComp::TakeDamage(AActor* DamgaedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCreator)
{
	

	
}




