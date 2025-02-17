// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "PacManGameModeBase.generated.h"

/**
 * 
 */

enum class EGameState:short {
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};

UCLASS()
class PACMAN_API APacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	EGameState GetCurrentGameState()const;

	void SetCurrentGameState(EGameState NewGameState);

	void SetEnemyVulerable();
	
private:
	EGameState CurrentGameState;
	TArray<AEnemyCharacter*> Enemies;
	
};

FORCEINLINE EGameState APacManGameModeBase::GetCurrentGameState()const
{
	return CurrentGameState;
}



