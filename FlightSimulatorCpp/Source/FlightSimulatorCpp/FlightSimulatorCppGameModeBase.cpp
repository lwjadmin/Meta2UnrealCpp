// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlightSimulatorCppGameModeBase.h"
#include "PlayerFlight.h"

AFlightSimulatorCppGameModeBase::AFlightSimulatorCppGameModeBase()
{
    DefaultPawnClass = APlayerFlight::StaticClass();
}
