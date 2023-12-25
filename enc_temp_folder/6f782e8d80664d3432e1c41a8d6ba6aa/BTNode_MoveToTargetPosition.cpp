// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNode_MoveToTargetPosition.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTNode_MoveToTargetPosition::UBTNode_MoveToTargetPosition()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTNode_MoveToTargetPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::InProgress;
}

void UBTNode_MoveToTargetPosition::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	static const FName PositionName = FName(TEXT("TargetPosition"));

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!IsValid(ControllPawn))
	{
		return;
	}

	FVector Pos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(PositionName);

	FVector CurrentPos = ControllPawn->GetActorLocation();

	FVector Dir = Pos - CurrentPos;
	Dir.Normalize();

	ControllPawn->AddMovementInput(Dir);

	if ((Pos - CurrentPos).Length() < 20)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}



}