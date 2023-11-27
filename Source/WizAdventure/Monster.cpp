// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "HealthComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::HandleHit()
{
	PlayAnimMontage(HitMontage);
	// 사운드
}

void AMonster::HandleDestruction()
{
	// 애니메이션 + Destroy
	OnDead();
	// 사운드
	// 점수는 게임모드에서
	
}