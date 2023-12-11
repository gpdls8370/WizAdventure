// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WizAdventureGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WIZADVENTURE_API AWizAdventureGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* Actor);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMonster(int32 NowMonsterCount);

	UFUNCTION(BlueprintImplementableEvent)
	void GameClear();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver();

protected:
	virtual void BeginPlay() override;

private:
	int32 MonsterCount;

	void SetPlayerInput(bool Enable);

	class AWizard *Wizard;
};