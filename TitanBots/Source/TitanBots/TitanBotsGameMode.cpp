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

	bool bIsNFC = false;

	if (!bIsNFC)
	{
		FPlatformProcess::CreateProc(TEXT("C:\\Users\\CHADALAK\\Desktop\\NFCPlugin.exe"), nullptr, true, false, false, nullptr, 0, nullptr, nullptr);
	}
	else
	{

	}
}
