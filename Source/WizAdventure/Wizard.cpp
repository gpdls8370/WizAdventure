// Fill out your copyright notice in the Description page of Project Settings.

#include "Wizard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

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

	SetCameraView(DeltaTime);
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

	Projectile->SetDamage(FireDamage);
	Projectile->SetOwner(this);
}

void AWizard::HandleHit()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), FRotator::ZeroRotator, FVector(0.5f));
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
}

void AWizard::HandleDestruction()
{
	PlayAnimMontage(DieMontage);
}

void AWizard::CombatToggle()
{
	bCombatMode = !bCombatMode;
	SetMovementInput(bCombatMode);
	GetCharacterMovement()->MaxWalkSpeed = bCombatMode ? CombatSpeed : NormalSpeed;
	AnimationChange(bCombatMode);
	bCameraMoving = true;
}

void AWizard::SetMovementInput(bool bFixedFront)
{
	bUseControllerRotationYaw = bFixedFront;
	GetCharacterMovement()->bOrientRotationToMovement = !bFixedFront;
}

void AWizard::SetCameraView(float DeltaTime)
{
	if (!bCameraMoving) return;

	if (MoveTime > MoveDuration)
	{
		bCameraMoving = false;
		MoveTime = 0;
		return;
	}

	MoveTime += DeltaTime;
	float alpha = MoveTime / MoveDuration;

	if (bCombatMode)
	{
		SpringArm->TargetArmLength = FMath::Lerp(500.f, 300.f, alpha);
		SpringArm->SetRelativeLocation(FMath::Lerp(FVector(0, 0, 75), FVector(0, 40, 95), alpha));
		SpringArm->SocketOffset = FMath::Lerp(FVector::ZeroVector, FVector(0, 30, 0), alpha);
		StaffMesh->SetRelativeRotation(FMath::Lerp(FRotator::ZeroRotator, FRotator(1.5, 4, -9), alpha));
	}
	else
	{
		SpringArm->TargetArmLength = FMath::Lerp(300.f, 500.f, alpha);
		SpringArm->SetRelativeLocation(FMath::Lerp(FVector(0, 40, 95), FVector(0, 0, 75), alpha));
		SpringArm->SocketOffset = FMath::Lerp(FVector(0, 30, 0), FVector::ZeroVector, alpha);
		StaffMesh->SetRelativeRotation(FMath::Lerp(FRotator(1.5, 4, -9), FRotator::ZeroRotator, alpha));
	}
}

float AWizard::GetHealth()
{
	UHealthComponent *HealthComp = GetComponentByClass<UHealthComponent>();
	if (HealthComp)
	{
		return HealthComp->GetHealth();
	}
	return 0;
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