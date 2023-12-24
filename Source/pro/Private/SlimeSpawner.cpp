// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeSpawner.h"

// Sets default values
ASlimeSpawner::ASlimeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASlimeSpawner::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &ASlimeSpawner::SpawnMonster, 2, true, 3);
}

// Called every frame
void ASlimeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlimeSpawner::SpawnMonster()
{
	FTransform Transform;
	Transform.SetLocation(GetActorLocation());

	GetWorld()->SpawnActor<ACharacterBase>(Monster, Transform);
}

