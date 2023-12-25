// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNode_RandomPosition.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTNode_RandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    static const FName PositionName = FName(TEXT("TargetPosition"));

    Super::ExecuteTask(OwnerComp, NodeMemory);

    FVector Position = FVector(FMath::RandRange(100, 2900), FMath::RandRange(100, 2900), 0);

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(PositionName, Position);

    return EBTNodeResult::Succeeded;
}

