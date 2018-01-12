// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelMaker.h"
#include "Components/BillboardComponent.h"
#include "Components/StaticMeshComponent.h"

#pragma region Main
// Sets default values
ALevelMaker::ALevelMaker()
{
	SceneRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneRootComp;

	IconComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard Compoennt"));
	IconComp->SetupAttachment(RootComponent);


	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALevelMaker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelMaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma endregion

#pragma region Level Maker Controller

void ALevelMaker::MakeGround()
{
	SpawnedGroundPlane.Empty();

	for (int32 Col = 0; Col < NumberOfColumn; Col++)
	{
		for (int32 Row = 0; Row < NumberOfRow; Row++)
		{
			FVector Loc = FVector();
			Loc.Y = Row * 100.0f;

			UStaticMeshComponent* CurrentMeshComp = NewObject<UStaticMeshComponent>(this);
			if (CurrentMeshComp)
			{
				CurrentMeshComp->RegisterComponentWithWorld(GetWorld());
				FAttachmentTransformRules ATR = FAttachmentTransformRules(EAttachmentRule::KeepWorld, false);
				CurrentMeshComp->AttachToComponent(RootComponent, ATR);
				AddOwnedComponent(CurrentMeshComp);
				CurrentMeshComp->SetWorldLocation(Loc);

				SpawnedGroundPlane.Add(CurrentMeshComp);
			}
		}
	}
}

#pragma endregion