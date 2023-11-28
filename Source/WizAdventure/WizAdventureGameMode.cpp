// Fill out your copyright notice in the Description page of Project Settings.


#include "WizAdventureGameMode.h"
#include "Wizard.h"
#include "Monster.h"
#include "Kismet/GameplayStatics.h"

void AWizAdventureGameMode::ActorDied(AActor *Actor)
{
	if (AWizard *Wizard = Cast<AWizard>(Actor))
	{
		// Á¾·á
		GameOver();
	}
	else if (AMonster *Monster = Cast<AMonster>(Actor))
	{
		MonsterCount--;
		UpdateMonster(MonsterCount);
		Monster->HandleDestruction();

		if (MonsterCount == 0)
		{
			GameClear();
		}
	}
}

void AWizAdventureGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Array;
	UGameplayStatics::GetAllActorsOfClass(this, AMonster::StaticClass(), Array);
	MonsterCount = Array.Num();

	UpdateMonster(MonsterCount);
}