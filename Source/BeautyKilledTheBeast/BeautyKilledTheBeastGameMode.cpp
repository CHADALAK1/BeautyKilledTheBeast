// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BeautyKilledTheBeast.h"
#include "BeautyKilledTheBeastGameMode.h"
#include "BeautyKilledTheBeastCharacter.h"

ABeautyKilledTheBeastGameMode::ABeautyKilledTheBeastGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/BKTBPlayerController_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
    if(PlayerControllerBPClass.Class != NULL)
    {
        PlayerControllerClass = PlayerControllerBPClass.Class;
    }
}
