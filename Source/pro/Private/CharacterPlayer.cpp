// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayer.h"
#include "CharacterAnimInstance.h"

#include "HUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/TextBlock.h"

ACharacterPlayer::ACharacterPlayer()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(Userwidget))
	{
		HUDWidget = Cast<UHUDWidget>(CreateWidget(GetWorld(), Userwidget));
	}

	if (HUDWidget.IsValid())
	{
		HUDWidget->AddToViewport();
		FString StringText = FString::Printf(TEXT("%d"), GetHP());
		FText TextText = FText::FromString(StringText);
		HUDWidget.Get()->HPText->SetText(TextText);

	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACharacterPlayer::Move(const FInputActionValue& Value)
{
	if (bIsDead)
	{
		return;
	}

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACharacterPlayer::Look(const FInputActionValue& Value)
{
	if (bIsDead)
	{
		return;
	}

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::Look);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::Attack);
	}
}


void ACharacterPlayer::Die()
{
	if (HUDWidget.IsValid())
	{
		HUDWidget->RemoveFromParent();
	}
	
	bIsDead = true;
}

void ACharacterPlayer::GetAttacked(int32 Damage)
{
	Super::GetAttacked(Damage);
	if (HUDWidget.IsValid())
	{
		FString StringText = FString::Printf(TEXT("%d"), GetHP());
		FText TextText = FText::FromString(StringText);
		HUDWidget->HPText->SetText(TextText);
	}
}

void ACharacterPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


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
	AnimInstance->Speed = GetVelocity().Length();
	AnimInstance->Angle = GetControlRotation().Pitch;
}
