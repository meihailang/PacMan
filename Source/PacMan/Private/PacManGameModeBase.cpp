// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMan/Public/PacManGameModeBase.h"

#include "EngineUtils.h"

void APacManGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentGameState(EGameState::EMenu);
	
	for(TActorIterator<AEnemyCharacter> EnemyIer(GetWorld());EnemyIer;++EnemyIer)
	{
		AEnemyCharacter* enemy = Cast<AEnemyCharacter>(*EnemyIer);
		if(enemy)
		{
			Enemies.Add(enemy);
		}
		
	}
}

void APacManGameModeBase::SetCurrentGameState(EGameState NewGameState)
{
	CurrentGameState = NewGameState;
	
	switch (CurrentGameState)
	{
	case EGameState::EPlaying:
		for(auto Iter(Enemies.CreateIterator());Iter;++Iter)
		{
			(*Iter)->SetMove(true);
		}
		break;
	case EGameState::EPause:
		for(auto Iter(Enemies.CreateIterator());Iter;++Iter)
		{
			(*Iter)->SetMove(false);
		}
		break;
	case EGameState::EWin:
		for(auto Iter(Enemies.CreateIterator());Iter;++Iter)
		{
			(*Iter)->Destroy();
		}
		break;
	case EGameState::EGameOver:
		for(auto Iter(Enemies.CreateIterator());Iter;++Iter)
		{
			(*Iter)->Destroy();
		}
		break;
	default:
		break;
	}
}

void APacManGameModeBase::SetEnemyVulerable()
{
	for(auto Iter(Enemies.CreateIterator());Iter;++Iter)
	{
		(*Iter)->SetVulnerable();
	}
}
