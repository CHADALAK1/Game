// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "MatchState.generated.h"

/**
 * 
 */
UCLASS()
class TITANBOTS_API UMatchState : public USaveGame
{
	GENERATED_BODY()
	
public:
    UMatchState();
    
    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Result)
    bool bPlayerHasWon;
    
    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Result)
    FString SaveSlotName;
    
    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Result)
    int32 UserIndex;
	
	
};
