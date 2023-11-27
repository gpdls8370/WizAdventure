// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "WizAdventureGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamaged);

	GameMode = Cast<AWizAdventureGameMode>(UGameplayStatics::GetGameMode(this));
	Health = MaxHealth;
}


void UHealthComponent::OnDamaged(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *Instigator, AActor *DamageCauser)
{
	Health -= Damage;

	if (Health <= 0.f && GameMode)
	{
		// ���� ó��
		Health = 0.f;
		HitDelegate.Broadcast(true);
		GameMode->ActorDied(GetOwner());
	}
	else
	{
		HitDelegate.Broadcast(false);
	}
}