// Fill out your copyright notice in the Description page of Project Settings.

#include "DynaSaveGame.h"
#include "Kismet/GameplayStatics.h"


UDynaSaveGame::UDynaSaveGame()
{
	SaveSlotPlayerOne = TEXT("DynaSaveSlotP1");
	SaveSlotPlayerTwo = TEXT("DynaSaveSlotP2");
	UserIndex = 0;
}

