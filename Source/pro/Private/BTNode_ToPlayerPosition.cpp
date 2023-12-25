// Fill out your copyright notice in the Description page of Project Settings.

#include "BTNode_ToPlayerPosition.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/GameplayStatics.h>

UBTNode_ToPlayerPosition::UBTNode_ToPlayerPosition()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTNode_ToPlayerPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::InProgress;
}

void UBTNode_ToPlayerPosition::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	static const FName TargetName = FName(TEXT("Target"));
	static const FName PositionName = FName(TEXT("TargetPosition"));

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!IsValid(ControllPawn))
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	APawn* Player = UGameplayStatics::GetPlayerPawn(World, 0);
	if (!IsValid(Player))
	{
		return;
	}

	FVector Pos = Player->GetActorLocation();

	FVector CurrentPos = ControllPawn->GetActorLocation();

	FVector Dir = Pos - CurrentPos;

	Dir.Normalize();

	ControllPawn->AddMovementInput(Dir);

	if (!IsValid(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetName)))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
