// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class PACMAN_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Body")
	UStaticMeshComponent* EnemyBody;

	void SetVulnerable();
	void SetInVulnerable();

	void SetMove(bool bMoveIt);
	void Killed();
	void ReArm();
	UFUNCTION()
	void OnCollision(class UPrimitiveComponent* HitComp,class AActor*OtherActor,class UPrimitiveComponent* OtherComp,int OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	bool bIsDead;
private:
	class UMaterialInterface* DefaultMaterial;
	class UMaterialInterface* VulnerableMaterial;
	FTimerHandle VulnerableTimer;
	bool bIsVulnerable;
	
};
