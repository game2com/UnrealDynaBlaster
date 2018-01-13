// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DynaSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDYNABLASTER_API UDynaSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UDynaSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int32 FirstPlayerScore;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int32 SecondPlayerScore;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotPlayerOne;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotPlayerTwo;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;
};
