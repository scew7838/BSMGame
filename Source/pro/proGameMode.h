// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "proGameMode.generated.h"

UCLASS(minimalapi)
class AproGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AproGameMode();
	virtual void BeginPlay() override;
	virtual void LoadLevel();
};



