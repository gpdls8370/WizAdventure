// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Wizard.generated.h"

UCLASS()
class WIZADVENTURE_API AWizard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWizard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void AnimationChange(bool bCombat);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void OnAttackEnd() { bAttacking = false; };

	UFUNCTION(BlueprintCallable)
	void HandleHit();

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent *SpringArm;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *StaffMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent *ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage *AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireDamage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem *HitParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShake;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void CombatToggle();

	void Attack();
	bool bAttacking = false;

	void SetMovementInput(bool bFixedFront);
	void SetCameraView(float DeltaTime);

	bool bCombatMode = false;
	float NormalSpeed = 600.f;
	float CombatSpeed = 200.f;

	bool bCameraMoving = false;
	float MoveTime = 0.f;
	float MoveDuration = 0.2f;
};
