// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttack.h"
#include "Components/SphereComponent.h"
#include "Monster.h"
#include <Kismet/GameplayStatics.h>

void UMeleeAttack::BeginPlay()
{
	Super::BeginPlay();
}

void UMeleeAttack::SetHitEvent()
{
	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &UMeleeAttack::OnOverlapBegin);
}

void UMeleeAttack::Attack()
{
	if (AttackCollision == nullptr)
	{
		return;
	}

	AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle, 
		FTimerDelegate::CreateLambda([this]()
			{
				AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}),
		0.1f, false);
}

void UMeleeAttack::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	AActor *MyOwner = GetOwner();

	if (MyOwner && OtherActor && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			AttackDamage,
			MyOwner->GetInstigatorController(),
			MyOwner,
			UDamageType::StaticClass()
		);
	}
}