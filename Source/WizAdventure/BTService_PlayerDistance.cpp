// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerDistance.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTService_PlayerDistance::UBTService_PlayerDistance()
{
	NodeName = TEXT("Update Player Location if in Range");
}

void UBTService_PlayerDistance::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AAIController *AIController = OwnerComp.GetAIOwner();

	if (!PlayerPawn || !AIController || !OwnerComp.GetBlackboardComponent())
	{
		return;
	}

	float TargetDist = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	float Dist = FVector::Dist(PlayerPawn->GetActorLocation(), AIController->GetPawn()->GetActorLocation());

	if (Dist < TargetDist)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}