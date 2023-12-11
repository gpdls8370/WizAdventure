// Fill out your copyright notice in the Description page of Project Settings.


#include "WizAdventureGameMode.h"
#include "Wizard.h"
#include "Monster.h"
#include "Kismet/GameplayStatics.h"

void AWizAdventureGameMode::ActorDied(AActor *Actor)
{
	if (Actor == Wizard)
	{
		Wizard->HandleDestruction();
		SetPlayerInput(false);
		GameOver();
	}
	else if (AMonster *Monster = Cast<AMonster>(Actor))
	{
		MonsterCount--;
		UpdateMonster(MonsterCount);
		Monster->HandleDestruction();

		if (MonsterCount == 0)
		{
			SetPlayerInput(false);
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

	Wizard = Cast<AWizard>(UGameplayStatics::GetPlayerCharacter(this, 0));

	UpdateMonster(MonsterCount);
}

void AWizAdventureGameMode::SetPlayerInput(bool Enable)
{
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController == nullptr)
	{
		return;
	}

	if (Enable)
	{
		Wizard->EnableInput(PlayerController);
		PlayerController->bShowMouseCursor = false;
	}
	else
	{
		Wizard->DisableInput(PlayerController);
		PlayerController->bShowMouseCursor = true;
	}
}