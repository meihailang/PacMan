// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMan/Public/Collections.h"
#include "Components/SphereComponent.h"

// Sets default values
ACollections::ACollections()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(true);
	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
	BaseCollectableComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollectableComponent"));
	CollectableMesh->SetupAttachment(BaseCollectableComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if(Sphere.Succeeded())
	{
		CollectableMesh->SetStaticMesh(Sphere.Object);
	}
	CollectableMesh->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
	BaseCollectableComponent->SetSphereRadius(16);
	BaseCollectableComponent->SetCanEverAffectNavigation(false);
	
}

// Called when the game starts or when spawned
void ACollections::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ACollections::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

