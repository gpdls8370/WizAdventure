// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster.h"

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	AMonster *Monster = Cast<AMonster>(GetPawn());

	if (AIBehavior || Monster)
	{
		RunBehaviorTree(AIBehavior);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), Monster->GetActorLocation());
		GetBlackboardComponent()->SetValueAsFloat(TEXT("DetectDistance"), Monster->DetectRange);
		GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackCooltime"), Monster->AttackCooltime);
	}
}

