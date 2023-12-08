// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class WIZADVENTURE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem *HitParticle;

	UFUNCTION(BlueprintImplementableEvent)
	void ProjectileHit();

	void SetDamage(float Value) { Damage = Value; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent *SphereComponent;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent *ProjectileMovement;

	UPROPERTY(EditAnywhere)
	float Speed = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 30.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
};
