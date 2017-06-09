// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine.h"

ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* Tank = GetPawn();

	FString PawnName = Tank->GetName();

	UE_LOG(LogTemp, Warning, TEXT("AI controller possesing pawn: %s"), *PawnName);

	FConstPlayerControllerIterator PlayerList = GetWorld()->GetPlayerControllerIterator();

	for (PlayerList; PlayerList; ++PlayerList)
	{
		const APlayerController* Player = *PlayerList;
		
		const APawn* Pawn = Player->GetPawn();

		if (Pawn) {
			UE_LOG(LogTemp, Warning, TEXT("AI Identifies enemy player at tank: %s"), *(Pawn->GetName()));
		}

	}
}

