// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeleeAttack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIZADVENTURE_API UMeleeAttack : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	void SetAttackCollision(class UShapeComponent *Value) { AttackCollision = Value; }

	UFUNCTION(BlueprintCallable)
	void SetHitEvent();

	UFUNCTION(BlueprintCallable)
	void Attack();

private:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackDamage = 10.f;

	class UShapeComponent *AttackCollision;
};
