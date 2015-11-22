// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "TitanBotsGameMode.generated.h"

/**
  EGameType
  Enum that holds the gamestate of the gamemode
 */
enum EGameType
{
    E_MatchBegin    UMETA(DisplayName = "MatchBegin"),
    E_MatchEnded    UMETA(DisplayName = "MatchEnded")
};

UCLASS(minimalapi)
class ATitanBotsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ATitanBotsGameMode();

	FProcHandle Handle1;
    
    EGameType GameType;
    
    virtual void Tick(float DeltaSeconds) override;

	void CloseNFCTech();
};



