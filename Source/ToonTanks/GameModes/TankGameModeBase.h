// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	private:

	APawnTank* PlayerTank;
	APlayerControllerBase* PlayerControllerRef;
	int32 TargetTurrets = 0;

	int32 GetTargetTurret();

	public:

	void ActorDied(AActor* DeadActor);
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

	protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;

	virtual void BeginPlay() override;
	UFUNCTION(blueprintImplementableEvent)	
	void GameStart();
	UFUNCTION(blueprintImplementableEvent)
	void GameOver(bool PlayerWon);

};
