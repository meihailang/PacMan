// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMan/Public/PacManCharactor.h"
#include"Collections.h"
#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Experimental/Chaos/Private/Chaos/CollisionOneShotManifolds.h"

// Sets default values
APacManCharactor::APacManCharactor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APacManCharactor::BeginPlay()
{
	Super::BeginPlay();
	Lives = 3;
	StartLocation = GetActorLocation();
	/*GetCharacterMovement()->SetMovementMode(MOVE_Flying);*/
	GameMode = Cast<APacManGameModeBase> (UGameplayStatics::GetGameMode(this));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharactor::OnCollision);

	for(TActorIterator<ACollections> collisionItr(GetWorld()); collisionItr; ++collisionItr)
	{
		CollectablesToEat++;
	}
	UE_LOG(LogTemp,Warning,TEXT("CollectablesToEat is %d"),CollectablesToEat);

}

// Called every frame
void APacManCharactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APacManCharactor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveX",this,&APacManCharactor::MoveXAxis);
	PlayerInputComponent->BindAxis("MoveY",this,&APacManCharactor::MoveYAxis);
	PlayerInputComponent->BindAction("NewGame",IE_Pressed,this,&APacManCharactor::NewGame);
	PlayerInputComponent->BindAction("ReStart",IE_Pressed,this,&APacManCharactor::ReStart);
	PlayerInputComponent->BindAction("Pause",IE_Pressed,this,&APacManCharactor::Pause);
}

void APacManCharactor::MoveXAxis(float AxisValue)
{
	if(GameMode->GetCurrentGameState() == EGameState::EPlaying)
	{
		CurrentVelocity.X = AxisValue;
		AddMovementInput(CurrentVelocity);
	}
	
}

void APacManCharactor::MoveYAxis(float AxisValue)
{
	if(GameMode->GetCurrentGameState() == EGameState::EPlaying)
	{
		CurrentVelocity.Y = AxisValue;
		AddMovementInput(CurrentVelocity);
	}
	
}

void APacManCharactor::ReStart()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("restartLevel"));
}

void APacManCharactor::NewGame()
{
	if(GameMode->GetCurrentGameState() == EGameState::EMenu)
	{
		GameMode->SetCurrentGameState(EGameState::EPlaying);
	}
}

void APacManCharactor::Pause()
{
	if(GameMode->GetCurrentGameState() == EGameState::EPlaying)
	{
		GameMode->SetCurrentGameState(EGameState::EPause);
	}else if(GameMode->GetCurrentGameState() == EGameState::EPause)
	{
		GameMode->SetCurrentGameState(EGameState::EPlaying);
	}
}

void APacManCharactor::Killed()
{
	if(--Lives == 0)
	{
		GameMode->SetCurrentGameState(EGameState::EGameOver);
	}else
	{
		SetActorLocation(StartLocation);
	}
}

void APacManCharactor::OnCollision(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
                                   class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(GameMode->GetCurrentGameState() == EGameState::EPlaying)
	{
		if(OtherActor->IsA(ACollections::StaticClass()))
		{
			ACollections* Collection = Cast<ACollections>(OtherActor);
			if(Collection->bIsSuperCollectable)
			{
				GameMode->SetEnemyVulerable();
			}
			OtherActor->Destroy();
			if(--CollectablesToEat == 0)
			{
				GameMode->SetCurrentGameState(EGameState::EWin);
			}
		}
	}
}

