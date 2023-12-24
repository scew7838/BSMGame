// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "CharacterBase.h"
#include "Engine/EngineTypes.h"
#include "CharacterPlayer.h"
#include "Camera/CameraComponent.h"

void UCharacterAnimInstance::AnimNotify_DieEnd()
{
	ACharacterBase* Character = Cast<ACharacterBase>(GetOwningActor());
	if (!IsValid(Character))
	{
		return;
	}
	Character->Die();
}

void UCharacterAnimInstance::AnimNotify_Attack()
{
	const UWorld* CurrentWorld = GetWorld();
	if (!IsValid(CurrentWorld))
	{
		return;
	}
	ACharacterBase* Character = Cast<ACharacterBase>(GetOwningActor());
	if (!IsValid(Character))
	{
		return;
	}

	FVector Startpos;
	FVector Endpos;

	ACharacterPlayer* Player = Cast<ACharacterPlayer>(Character);
	if (IsValid(Player))
	{
		UCameraComponent* Camera = Player->GetFollowCamera();
		Startpos = Camera->GetComponentLocation() + Camera->GetForwardVector() * 100;
		Endpos = Camera->GetComponentLocation() + Camera->GetForwardVector() * 1100;
	}
	else
	{
		Startpos = Character->GetActorLocation() + FVector::UpVector * 10.0f;
		Endpos = Startpos + Character->GetActorForwardVector() * 1000.0f;
	}
	

	FHitResult Hitreseult;
	
	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(Character);
	CurrentWorld->LineTraceSingleByChannel(Hitreseult, Startpos, Endpos, ECollisionChannel::ECC_Camera, params);

	ACharacterBase* HitedCharacter = Cast<ACharacterBase>(Hitreseult.GetActor());
	if (!IsValid(HitedCharacter))
	{
		return;
	}

	HitedCharacter->GetAttacked(Character->GetAD());
}

void UCharacterAnimInstance::AnimNotify_AttackEnd()
{
	bIsAttacking = false;
}
