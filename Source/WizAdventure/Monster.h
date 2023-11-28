// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class WIZADVENTURE_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	UAnimMontage *DieMontage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDead();

	UFUNCTION(BlueprintCallable)
	void HandleHit();

	void HandleDestruction();

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage *HitMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage *AttackMontage;
};