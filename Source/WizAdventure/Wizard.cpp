// Fill out your copyright notice in the Description page of Project Settings.

#include "Wizard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWizard::AWizard()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);

	StaffMesh = CreateDefaultSubobject<UStaticMeshComponent>("Staff Mesh");
	StaffMesh->SetupAttachment(GetMesh() , "WeaponSocket");

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

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
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &AWizard::Attack);
	PlayerInputComponent->BindAction("CombatToggle", EInputEvent::IE_Pressed, this, &AWizard::CombatToggle);
}

void AWizard::MoveForward(float AxisValue)
{
	if (!bAttacking && (Controller != nullptr) && (AxisValue != 0.0f))
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
	if (!bAttacking && (Controller != nullptr) && (AxisValue != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 화면 회전에 대해 오른쪽 벡터(y축) 추출
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue);
	}
}

void AWizard::Attack()
{
	if (!bCombatMode || bAttacking) return;

	bAttacking = true;

	// Attack 애니메이션 중간에 Fire이 실행 됨
	PlayAnimMontage(AttackMontage);
}

void AWizard::Fire()
{
	FVector Location; FRotator Rotator;
	Controller->GetPlayerViewPoint(Location, Rotator);

	AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(
	ProjectileClass,
	ProjectileSpawnPoint->GetComponentLocation(),
	Rotator
	);
}

void AWizard::CombatToggle()
{
	bCombatMode = !bCombatMode;
	SetMovementInput(bCombatMode);
	GetCharacterMovement()->MaxWalkSpeed = bCombatMode ? CombatSpeed : NormalSpeed;
	AnimationChange(bCombatMode);
	SetCameraView(bCombatMode);
	if (bCombatMode)
	{
		ShowCombatUI(bCombatMode);
	}
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
		SpringArm->SetRelativeLocation(FVector(0 , 40 , 75));
		SpringArm->SocketOffset = FVector(0 , 30 , 0);
		StaffMesh->SetRelativeRotation(FRotator(1.5, 4, -9));
	}
	else
	{
		SpringArm->TargetArmLength = 500.f;
		SpringArm->SetRelativeLocation(FVector(0, 0, 75));
		SpringArm->SocketOffset = FVector::ZeroVector;
		StaffMesh->SetRelativeRotation(FRotator::ZeroRotator);
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