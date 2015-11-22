// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TitanBots.h"
#include "TitanBotsGameMode.h"
#include "TitanBotsCharacter.h"
#include "TitanBotsPlayerController.h"

ATitanBotsGameMode::ATitanBotsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/TBPlayerController_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	Handle1 = FPlatformProcess::CreateProc(TEXT("C:\\Temp\\NFCPlugin.exe"), nullptr, true, false, false, nullptr, 0, nullptr, nullptr);

}

void ATitanBotsGameMode::CloseNFCTech()
{
	FPlatformProcess::CloseProc(Handle1);
}

void ATitanBotsGameMode::Tick(float DeltaSeconds)
{
    ATitanBotsPlayerController* PC = (ATitanBotsPlayerController*)GetWorld()->GetFirstPlayerController();
    ATitanBotsCharacter* Char = (ATitanBotsCharacter*)PC->GetControlledPawn();
    
    if(!PC->bIsInGarage)
    {
        StartMatch();
    }
    else
    {
        EndMatch();
    }
}