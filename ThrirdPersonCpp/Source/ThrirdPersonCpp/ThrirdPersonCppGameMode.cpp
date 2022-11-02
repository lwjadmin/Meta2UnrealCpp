// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThrirdPersonCppGameMode.h"
#include "ThrirdPersonCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "MyCharacter.h"

AThrirdPersonCppGameMode::AThrirdPersonCppGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	DefaultPawnClass = AMyCharacter::StaticClass();
}
