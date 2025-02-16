// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include"EnemyCharacter.h"
#include "NavigationSystem.h"
#include "PacManGameModeBase.h"
#include "AIEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API AAIEnemy : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	auto SearchNewPoint() -> void;
	void GoHome();
	void ReArm();
	void StopMove();
private:
	class AEnemyCharacter*Bot;
	FVector HomeLocation;
	FTimerHandle TimerHandle;
	APacManGameModeBase* GameMode;
};


