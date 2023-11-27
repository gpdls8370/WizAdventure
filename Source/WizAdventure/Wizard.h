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

	UFUNCTION(BlueprintImplementableEvent)
	void ShowCombatUI(bool bCombat);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void OnAttackEnd() { bAttacking = false; };

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

	void MoveForward(float Value);
	void MoveRight(float Value);
	void CombatToggle();

	void Attack();
	bool bAttacking = false;

	void SetMovementInput(bool bFixedFront);
	void SetCameraView(bool bFixedFront);

	bool bCombatMode = false;
	float NormalSpeed = 500.f;
	float CombatSpeed = 200.f;
};
