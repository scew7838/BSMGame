// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class PRO_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual int32 GetHP();
	virtual int32 GetAD();
	virtual void GetAttacked(int32 Damage);
	virtual void Die();
	virtual void Attack();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HP, meta = (AllowPrivateAccess = "true"))
	int32 FullHP;

	int32 CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Armor, meta = (AllowPrivateAccess = "true"))
	int32 AD;

protected:
	bool bIsDead;

};
