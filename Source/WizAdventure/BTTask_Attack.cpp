// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Monster.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AMonster *Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (Monster == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Monster->Attack();

	return EBTNodeResult::Succeeded;
}

