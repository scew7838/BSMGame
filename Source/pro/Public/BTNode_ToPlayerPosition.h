// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTNode_ToPlayerPosition.generated.h"

UCLASS()
class PRO_API UBTNode_ToPlayerPosition : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTNode_ToPlayerPosition();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
	
};
