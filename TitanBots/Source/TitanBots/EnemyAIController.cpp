// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "TitanBotsCharacter.h"
#include "TitanBotsGameMode.h"
#include "EnemyAIController.h"



AEnemyAIController::AEnemyAIController()
{
    PrimaryActorTick.bCanEverTick = true;
	SetClassType(AIClassType::E_AILight);
}

void AEnemyAIController::SetClassType(AIClassType Type)
{
	TypeClass = Type;
}