// Fill out your copyright notice in the Description page of Project Settings.

#include "Wizard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/SpringArmComponent.h>

// Sets default values
AWizard::AWizard()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWizard::BeginPlay()
{
	Super::BeginPlay();

	SetMovementInput(bCombatMode);
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWizard::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWizard::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("CombatToggle", EInputEvent::IE_Pressed, this, &AWizard::CombatToggle);
}

void AWizard::MoveForward(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		// 마우스 회전 고려 (Yaw 회전만 반영함)
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 화면 회전에 대해 정면 벡터(x축) 추출
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
	
}

void AWizard::MoveRight(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);


		// 화면 회전에 대해 오른쪽 벡터(y축) 추출
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue);
	}
}

void AWizard::CombatToggle()
{
	bCombatMode = !bCombatMode;
	SetMovementInput(bCombatMode);
	GetCharacterMovement()->MaxWalkSpeed = bCombatMode ? CombatSpeed : NormalSpeed;
	AnimationChange(bCombatMode);
	SetCameraView(bCombatMode);
}

void AWizard::SetMovementInput(bool bFixedFront)
{
	bUseControllerRotationYaw = bFixedFront;
	GetCharacterMovement()->bOrientRotationToMovement = !bFixedFront;
}

void AWizard::SetCameraView(bool bFixedFront)
{
	if (bFixedFront)
	{
		SpringArm->TargetArmLength = 300.f;
		SpringArm->SetRelativeLocation(FVector(20 , 40 , 55));
		SpringArm->SocketOffset = FVector(0 , 30 , 0);
		//Cast<APlayerController>(Controller)->bShowMouseCursor = true;
	}
	else
	{
		SpringArm->TargetArmLength = 500.f;
		SpringArm->SetRelativeLocation(FVector::ZeroVector);
		SpringArm->SocketOffset = FVector::ZeroVector;
		//Cast<APlayerController>(Controller)->bShowMouseCursor = false;
	}
}

// 콘솔일 경우에 사용
// void AWizard::Lookup(float Value)
// {
// 	// Pitch 바꿔주기
// 	AddControllerPitchInput(Value * Sensitivity * GetWorld()->GetDeltaSeconds());

// }

// void AWizard::Turn(float Value)
// {
// 	// Yaw 바꿔주기
// 	AddControllerYawInput(Value * Sensitivity * GetWorld()->GetDeltaSeconds());
// }