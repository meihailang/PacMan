// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "AIEnemy.h"
#include "PacManCharactor.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CylinerderObj(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if(CylinerderObj.Succeeded())
	{
		EnemyBody->SetStaticMesh(CylinerderObj.Object);
	}
	EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.0f));
	EnemyBody->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	EnemyBody->SetupAttachment(RootComponent);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);

	static ConstructorHelpers::FObjectFinder<UMaterial>VulnerableM(TEXT("/Script/Engine.Material'/Game/Materials/M_Enemy_Vulnerable.M_Enemy_Vulnerable'"));
	SetActorEnableCollision(true);
	AIControllerClass = AAIEnemy::StaticClass();
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaterial = EnemyBody->GetMaterial(0);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnCollision);
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::SetVulnerable()
{
	GetWorldTimerManager().SetTimer(VulnerableTimer,this,&AEnemyCharacter::SetInVulnerable,10.0f,false);
	if(bIsVulnerable)
	{
		return;
	}
	bIsVulnerable = true;
	EnemyBody->SetMaterial(0,VulnerableMaterial);
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}

void AEnemyCharacter::SetInVulnerable()
{
	GetWorldTimerManager().ClearTimer(VulnerableTimer);
	bIsVulnerable = false;
	EnemyBody->SetMaterial(0,DefaultMaterial);
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void AEnemyCharacter::SetMove(bool bMoveIt)
{
	AAIEnemy* AI = Cast<AAIEnemy>(GetController());
	if(bMoveIt)
	{
		AI->SearchNewPoint();
	}else
	{
		AI->StopMove();
	}
}

void AEnemyCharacter::Killed()
{
	if(bIsDead)
	{
		return;
	}
	bIsDead = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	AAIEnemy* AI = Cast<AAIEnemy>(GetController());
	AI->GoHome();
}

void AEnemyCharacter::ReArm()
{
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	if(bIsVulnerable)
	{
		SetInVulnerable();
	}
	SetMove(true);
}

void AEnemyCharacter::OnCollision(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
								   class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(APacManCharactor::StaticClass()))
	{
		if(bIsVulnerable)
		{
			Killed();
		}else
		{
			APacManCharactor* PacMan = Cast<APacManCharactor>(OtherActor);
			PacMan->Killed();
		}
	}
}



