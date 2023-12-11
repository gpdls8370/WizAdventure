// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate, bool, bDead);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WIZADVENTURE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintAssignable)
	FDelegate HitDelegate;	// Hit시 이벤트, 블루프린트로 구현

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const { return Health / MaxHealth; };

	float GetHealth() const { return Health; };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere);
	float MaxHealth = 100.f;
	float Health;

	class AWizAdventureGameMode* GameMode;

	UFUNCTION()
	void OnDamaged(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *Instigator, AActor *DamageCauser);
};
