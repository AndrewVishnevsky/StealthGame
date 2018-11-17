// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InsigatorPawn)
{
	if (InsigatorPawn)
	{
		InsigatorPawn->DisableInput(nullptr);
		
		//AActor* EndGameViewTarget;

		//UGameplayStatics::
		
		APlayerController* PC = Cast<APlayerController>(InsigatorPawn->GetController());
		if (PC)
		{
			PC->SetViewTargetWithBlend(nullptr, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
	OnMissionCompleted(InsigatorPawn);
	
}


