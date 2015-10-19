// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include <string>
#include "TitanBotsCharacter.h"
#include "TitanBotsPlayerController.h"


void ATitanBotsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TCPConnectionListener();
}


//TCP Connection Listener
void ATitanBotsPlayerController::TCPConnectionListener()
{

	//~~~~~~~~~~~~~
	//if (!ListenerSocket)
	//{
	//	return;
	//}
	//~~~~~~~~~~~~~
	ConnectionSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	FIPv4Address ip;
	FString address = TEXT("127.0.0.1");
	FIPv4Address::Parse(address, ip);
	RemoteAddress->SetIp(ip.GetValue());
	RemoteAddress->SetPort(7000);
	bool Pending = ConnectionSocket->Connect(*RemoteAddress);

	// handle incoming connections
	if (Pending)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, "OH YEA!");
		ClientMessage("Hello");

		if (ConnectionSocket != NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, "Socket Connected");
			//Global cache of current Remote Address
			RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);

			//can thread this too
			GetWorldTimerManager().SetTimer(Timer02, this, &ATitanBotsPlayerController::TCPSocketListener, 0.01, true);
		}

	}
}


//This function requires
//		#include <string>
FString ATitanBotsPlayerController::StringFromBinaryArray(const TArray<uint8>& BinaryArray)
{
	//Create a string from a byte array!
	std::string cstr(reinterpret_cast<const char*>(BinaryArray.GetData()), BinaryArray.Num());
	return FString(cstr.c_str());
}


void ATitanBotsPlayerController::TCPSocketListener()
{
	//~~~~~~~~~~~~~
	if (!ConnectionSocket) return;
	//~~~~~~~~~~~~~


	//Binary Array!
	TArray<uint8> ReceivedData;

	uint32 Size;
	while (ConnectionSocket->HasPendingData(Size))
	{
		ReceivedData.Init(FMath::Min(Size, 65507u));

		int32 Read = 0;
		ConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (ReceivedData.Num() <= 0)
	{
		//No Data Received
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Bytes Read ~> %d"), ReceivedData.Num()));


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//						String From Binary Array
	const FString ReceivedUE4String = StringFromBinaryArray(ReceivedData);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	ATitanBotsCharacter *Char = (ATitanBotsCharacter*)this->GetControlledPawn();

	Char->CharacterMeshID = ReceivedUE4String;

	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("As String Data ~> %s"), *ReceivedUE4String));
}