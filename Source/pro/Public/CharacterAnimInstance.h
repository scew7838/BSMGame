// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRO_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Trigger)
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Trigger)
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Trigger)
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Trigger)
	float Angle;

	UFUNCTION()
	void AnimNotify_DieEnd();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_AttackEnd();

};
