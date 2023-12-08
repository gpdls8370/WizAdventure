// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedAttack.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

void URangedAttack::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void URangedAttack::Fire()
{
	FRotator Rotator = ( PlayerPawn->GetActorLocation() - GetOwner()->GetActorLocation() ).Rotation();

	AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		Rotator
	);

	Projectile->SetDamage(ProjectileDamage);
	Projectile->SetOwner(GetOwner());
}
