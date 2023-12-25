// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_Detect::UBTService_Detect()
{
	Interval = 0.5f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	static const FName TargetName = FName(TEXT("Target"));
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* ControlPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!IsValid(ControlPawn))
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

	if ((Player->GetActorLocation() - ControlPawn->GetActorLocation()).Length() < 300)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetName, Player);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetName, nullptr);
	}
}
