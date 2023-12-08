// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>

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
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::HandleHit()
{
	PlayAnimMontage(HitMontage);
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
}

void AMonster::HandleDestruction()
{
	PlayAnimMontage(DieMontage);
	DelayDestroy();
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	// 점수는 게임모드에서
}

void AMonster::Attack()
{
	PlayAnimMontage(AttackMontage);
	// 애니메이션 공격 시점에서 OnAttack() 실행
}

