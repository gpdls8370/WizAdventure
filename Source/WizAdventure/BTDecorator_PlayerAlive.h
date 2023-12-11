// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_PlayerAlive.generated.h"

/**
 * 
 */
UCLASS()
class WIZADVENTURE_API UBTDecorator_PlayerAlive : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_PlayerAlive();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
