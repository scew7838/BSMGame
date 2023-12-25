// Copyright Epic Games, Inc. All Rights Reserved.

#include "proGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"

AproGameMode::AproGameMode()
{

}

void AproGameMode::BeginPlay()
{
	FTimerHandle handler;

	GetWorldTimerManager().SetTimer(handler, this, &AproGameMode::LoadLevel, 1, false, 5);

}

void AproGameMode::LoadLevel()
{
	FLatentActionInfo info;
	FLatentActionInfo info2;
	UGameplayStatics::LoadStreamLevel(this, FName("SlimeLevel"), true, true, info);
}
