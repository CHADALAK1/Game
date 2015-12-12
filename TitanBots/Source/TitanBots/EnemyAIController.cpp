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

void AEnemyAIController::Tick(float DeltaSeconds)
{
    ATitanBotsCharacter* Char = (ATitanBotsCharacter*)GetControlledPawn();
    ATitanBotsGameMode* GM = (ATitanBotsGameMode*)GetWorld()->GetAuthGameMode();
    
    if(Char)
    {
        if(Char->GetHealth() <= 0)
        {
            GM->GameType = EGameType::E_MatchEnded;
        }
    }
}

void AEnemyAIController::SetClassType(AIClassType Type)
{
	TypeClass = Type;
}