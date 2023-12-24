// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSlime.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>

ACharacterSlime::ACharacterSlime()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 100.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void ACharacterSlime::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ACharacterSlime::OnHit);
	SpawnDefaultController();
}

void ACharacterSlime::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	ACharacterBase* Player = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(World, 0));

	if (!IsValid(Player))
	{
		return;
	}
	
	FVector Dir = (Player->GetActorLocation() - GetActorLocation());
	
	Dir.Normalize();
	AddMovementInput(Dir);
}

void ACharacterSlime::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	ACharacterBase* Player = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(World, 0));

	if (!IsValid(Player))
	{
		return;
	}

	if (Player == OtherActor)
	{
		Player->GetAttacked(GetAD());
	}

	//원래는 즉사 메소드를 따로 만들어야함.
	GetAttacked(1000000);
}

void ACharacterSlime::GetAttacked(int32 Damage)
{
	Super::GetAttacked(Damage);
}




