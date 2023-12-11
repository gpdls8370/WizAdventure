// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_PlayerAlive.h"
#include "Kismet/GameplayStatics.h"
#include "Wizard.h"

UBTDecorator_PlayerAlive::UBTDecorator_PlayerAlive()
{
	NodeName = TEXT("Player is Alive?");
}

bool UBTDecorator_PlayerAlive::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
	AWizard *Wizard = Cast<AWizard>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Wizard == nullptr)
	{
		return false;
	}

	return Wizard->GetHealth() > 0;
}