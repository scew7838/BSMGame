// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CharacterSlime.generated.h"

UCLASS()
class PRO_API ACharacterSlime : public ACharacterBase
{
	GENERATED_BODY()

private:
	FComponentHitSignature DelegateToHIt;

public:
	ACharacterSlime();

protected:
	virtual void BeginPlay();

public:
	virtual void Tick(float DeltaSeconds);
	virtual void GetAttacked(int32 Damage) override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
