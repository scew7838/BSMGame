// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

void ACharacterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void ACharacterAIController::RunAI()
{

	UBlackboardComponent* BBCom = Blackboard.Get();

	if (UseBlackboard(BBAsset, BBCom))
	{
		RunBehaviorTree(BTAsset);
	}
}

void ACharacterAIController::StopAI()
{
	UBehaviorTreeComponent* BTCom = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (!IsValid(BTCom))
	{
		BTCom->StopTree();
	}
}
