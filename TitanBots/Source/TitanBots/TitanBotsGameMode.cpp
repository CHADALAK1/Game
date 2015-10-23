// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TitanBots.h"
#include "TitanBotsGameMode.h"
#include "TitanBotsCharacter.h"
#include "TitanBotsPlayerController.h"

ATitanBotsGameMode::ATitanBotsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerControllerClass = ATitanBotsPlayerController::StaticClass();

	Handle1 = FPlatformProcess::CreateProc(TEXT("C:\\Temp\\NFCPlugin.exe"), nullptr, true, false, false, nullptr, 0, nullptr, nullptr);

}

void ATitanBotsGameMode::CloseNFCTech()
{
	FPlatformProcess::CloseProc(Handle1);
	Handle1.Close();
}