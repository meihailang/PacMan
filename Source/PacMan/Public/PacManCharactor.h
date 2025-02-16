// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacManGameModeBase.h"
#include "PacManCharactor.generated.h"

UCLASS()
class PACMAN_API APacManCharactor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManCharactor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveXAxis(float AxisValue);

	void MoveYAxis(float AxisValue);

	void ReStart();

	void NewGame();

	void Pause();

	void Killed();
	
	UFUNCTION()
	void OnCollision(class UPrimitiveComponent* HitComp,class AActor*OtherActor,class UPrimitiveComponent* OtherComp,int OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	int CollectablesToEat;
	int Lives;
private:
	APacManGameModeBase* GameMode;
	FVector CurrentVelocity;
	
	FVector StartLocation;
};

