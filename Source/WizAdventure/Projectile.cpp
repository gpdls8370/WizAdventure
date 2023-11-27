// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/SphereComponent.h>
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovement->MaxSpeed = Speed;
	ProjectileMovement->InitialSpeed = Speed;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent ->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{	
	AActor *MyOwner = GetOwner();

	if (MyOwner && OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor, 
			Damage, 
			MyOwner->GetInstigatorController(),
			this, 
			UDamageType::StaticClass()
		);
	}

	// Hit ¿Ã∆Â∆Æ + Destroy
	ProjectileHit();
}
