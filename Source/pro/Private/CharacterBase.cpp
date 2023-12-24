// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "CharacterAnimInstance.h"
#include "Components/CapsuleComponent.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsDead = false;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = FullHP;
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int32 ACharacterBase::GetHP()
{
	return CurrentHP;
}

int32 ACharacterBase::GetAD()
{
	return AD;
}

void ACharacterBase::Die()
{
	Destroy();
}

void ACharacterBase::Attack()
{
	if (bIsDead)
	{
		return;
	}

	USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
	if (!IsValid(SkeletalMeshComp))
	{
		return;
	}
	UCharacterAnimInstance* AnimInstance = Cast<UCharacterAnimInstance>(SkeletalMeshComp->GetAnimInstance());
	if (!IsValid(AnimInstance))
	{
		return;
	}

	if (!AnimInstance->bIsAttacking)
	{
		AnimInstance->bIsAttacking = true;
	}

}


void ACharacterBase::GetAttacked(int32 Damage)
{
	CurrentHP -= Damage;
	if (CurrentHP <= 0)
	{
		CurrentHP = 0;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
		if (!IsValid(SkeletalMeshComp))
		{
			return;
		}
		UCharacterAnimInstance* AnimInstance = Cast<UCharacterAnimInstance>(SkeletalMeshComp->GetAnimInstance());
		if (!IsValid(AnimInstance))
		{
			return;
		}
		bIsDead = true;
		AnimInstance->bIsDead = true;
	}
}