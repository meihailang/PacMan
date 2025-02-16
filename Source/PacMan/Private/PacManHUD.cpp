// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManHUD.h"
#include "PacManGameModeBase.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "PacManCharactor.h"

void APacManHUD::DrawHUD()
{
	Super::DrawHUD();
	class APacManGameModeBase* GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
	switch(GameMode->GetCurrentGameState())
	{
	case EGameState::EMenu:
		DrawText(TEXT("Wellcome To PacMan!\n\nN to start a new game  \nP to pause the game"),FColor::White,Canvas->SizeX/2.0f-150.0f,Canvas->SizeY/2.0f-100.0f,HUDFont);
		break;
	case EGameState::EPlaying:
		{
			APacManCharactor* PacMan = Cast<APacManCharactor>(UGameplayStatics::GetPlayerPawn(this,0));
			if(PacMan)
			{
				FString LiveString=TEXT("Lives:") + FString::FromInt(PacMan->Lives);
				DrawText(LiveString,FColor::Green,50,50,HUDFont);
				FString CollectableToEatString=TEXT("CollectableToEat:") + FString::FromInt(PacMan->CollectablesToEat);
				DrawText(CollectableToEatString,FColor::Green,Canvas->SizeX-150.0f,50,HUDFont);	
			}
		}
		break;
	case EGameState::EPause:
		DrawText(TEXT("P to continue"),FColor::White,Canvas->SizeX/2.0f-150.0f,Canvas->SizeY/2.0f-100.0f,HUDFont);
		break;
		
	case EGameState::EWin:
		DrawText(TEXT("You Win!\n\n R for another"),FColor::White,Canvas->SizeX/2.0f-150.0f,Canvas->SizeY/2.0f-100.0f,HUDFont);
		break;
	case EGameState::EGameOver:
		DrawText(TEXT("Game Over!\n\n R for another"),FColor::White,Canvas->SizeX/2.0f-150.0f,Canvas->SizeY/2.0f-100.0f,HUDFont);
		break;
	default:
		break;
	}
}
