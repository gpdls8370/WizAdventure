// Fill out your copyright notice in the Description page of Project Settings.


#include "WizAdventureGameMode.h"
#include "Wizard.h"
#include "Monster.h"

void AWizAdventureGameMode::ActorDied(AActor *Actor)
{
	if (AWizard *Wizard = Cast<AWizard>(Actor))
	{
		// Á¾·á
	}
	else if (AMonster *Monster = Cast<AMonster>(Actor))
	{
		Monster->HandleDestruction();
	}
}