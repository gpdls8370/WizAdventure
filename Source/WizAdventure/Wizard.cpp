// Fill out your copyright notice in the Description page of Project Settings.


#include "Wizard.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AWizard::AWizard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

// Called when the game starts or when spawned
void AWizard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWizard::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWizard::MoveRight);
	PlayerInputComponent->BindAxis("Lookup", this, &AWizard::Lookup);
	PlayerInputComponent->BindAxis("Turn", this, &AWizard::Turn);
}

void AWizard::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// 현재 화면 좌우(Yaw) 회전 알아내기
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// FRotationMatrix로 바꿔서(계산 속도 향상) 전방 벡터 Direction 알아내기
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// 이동 시키기
		AddMovementInput(Direction, Value);
	}
}

void AWizard::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// 현재 화면 좌우(Yaw) 회전 알아내기
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Right 벡터 알아내기
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		// 이동 시키기
		AddMovementInput(Direction, Value);
	}
}

void AWizard::Lookup(float Value)
{
	// Pitch 바꿔주기
	AddControllerPitchInput(Value * Sensitivity * GetWorld()->GetDeltaSeconds());
	
}

void AWizard::Turn(float Value)
{
	// Yaw 바꿔주기
	AddControllerYawInput(Value * Sensitivity * GetWorld()->GetDeltaSeconds());
}