// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"

#include "Kismet/GameplayStatics.h"

void AAIEnemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Bot = Cast<AEnemyCharacter>(InPawn);
	HomeLocation = Bot->GetActorLocation();
	GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
	SearchNewPoint();
}

void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if(!Bot->bIsDead&&GameMode->GetCurrentGameState() != EGameState::EPause)
	{
		SearchNewPoint();
	}
}

void AAIEnemy::SearchNewPoint()
{
	UNavigationSystemV1* Navmesh = UNavigationSystemV1::GetCurrent(this);
	if(Navmesh)
	{
		const float SearchRadius = 10000.0f;
		FVector RandLocation;
		
		const bool bFound = Navmesh->K2_GetRandomReachablePointInRadius(this,Bot->GetActorLocation(),RandLocation, SearchRadius);
		if (bFound)
		{
			MoveToLocation(RandLocation);
		}
	}
}

void AAIEnemy::GoHome()
{
	MoveToLocation(HomeLocation);
	GetWorldTimerManager().SetTimer(TimerHandle,this,&AAIEnemy::ReArm,5.0f,false);
}

void AAIEnemy::ReArm()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	Bot->ReArm();
}

void AAIEnemy::StopMove()
{
	/*StopMovement();*/
	MoveToLocation(Bot->GetActorLocation());
}
