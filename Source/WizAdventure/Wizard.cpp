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
		// ���� ȭ�� �¿�(Yaw) ȸ�� �˾Ƴ���
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// FRotationMatrix�� �ٲ㼭(��� �ӵ� ���) ���� ���� Direction �˾Ƴ���
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// �̵� ��Ű��
		AddMovementInput(Direction, Value);
	}
}

void AWizard::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// ���� ȭ�� �¿�(Yaw) ȸ�� �˾Ƴ���
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Right ���� �˾Ƴ���
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		// �̵� ��Ű��
		AddMovementInput(Direction, Value);
	}
}

void AWizard::Lookup(float Value)
{
	// Pitch �ٲ��ֱ�
	AddControllerPitchInput(Value * Sensitivity * GetWorld()->GetDeltaSeconds());
	
}

void AWizard::Turn(float Value)
{
	// Yaw �ٲ��ֱ�
	AddControllerYawInput(Value * Sensitivity * GetWorld()->GetDeltaSeconds());
}