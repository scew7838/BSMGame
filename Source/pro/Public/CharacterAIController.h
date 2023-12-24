// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharacterAIController.generated.h"

UCLASS()
class PRO_API ACharacterAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* Pawn) override;

	void RunAI();
	void StopAI();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	class UBlackboardData* BBAsset;

};
