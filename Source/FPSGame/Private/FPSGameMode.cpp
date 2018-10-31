// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
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
		
		if (SpectatingViewpointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);


			//change viewtargets if any valid actor found
			
			if (ReturnedActors.Num() > 0)
			{
				AActor* EndGameViewTarget = ReturnedActors[0];

				APlayerController* PC = Cast<APlayerController>(InsigatorPawn->GetController());
				if (PC)
				{
					PC->SetViewTargetWithBlend(nullptr, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update Gamemode class with valid"));
		}

		
	}
	OnMissionCompleted(InsigatorPawn);
	
}


