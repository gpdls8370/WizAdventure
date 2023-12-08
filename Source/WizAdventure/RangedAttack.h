// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RangedAttack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIZADVENTURE_API URangedAttack : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void SetProjectileSpawnPoint(USceneComponent *Value) { ProjectileSpawnPoint = Value; }

private:
	USceneComponent *ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileDamage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	APawn *PlayerPawn;
};
