// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"


class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

	private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category  = "Combat", meta = (AllowPrivateAccess = "true"));
	float FireRate = 1.0f;
	float FireRange = 500.0f;
	FTimerHandle FireRateTimer;
	APawnTank* PlayerPawn;

	void CheckFireCondition();
	float ReturnDistanceToPlayer();

	protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

};
