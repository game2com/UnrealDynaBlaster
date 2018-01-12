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
	/*Clear previous ground*/
	if (SpawnedGroundPlane.Num() > 0)
	{
		for (UStaticMeshComponent* SM : SpawnedGroundPlane)
		{
			SM->DestroyComponent(true);
		}
	}
	SpawnedGroundPlane.Empty();

	/*Add new*/
	for (int32 Col = 0; Col < NumberOfColumn; Col++)
	{
		for (int32 Row = 0; Row < NumberOfRow; Row++)
		{
			FVector Loc = FVector::ZeroVector;
			Loc.Y = Row * SizeOfBlock;
			Loc.X = Col * SizeOfBlock;

			UStaticMeshComponent* CurrentMeshComp = NewObject<UStaticMeshComponent>(this);
			if (CurrentMeshComp)
			{
				CurrentMeshComp->RegisterComponentWithWorld(GetWorld());
				FAttachmentTransformRules ATR = FAttachmentTransformRules(EAttachmentRule::KeepWorld, false);
				CurrentMeshComp->AttachToComponent(RootComponent, ATR);
				AddOwnedComponent(CurrentMeshComp);
				CurrentMeshComp->SetWorldLocation(Loc);
				CurrentMeshComp->SetStaticMesh(PlaneMesh);
				CurrentMeshComp->SetMaterial(0, PlaneMaterial);
				/*Store in array*/
				SpawnedGroundPlane.Add(CurrentMeshComp);
			}
		}
	}
}

#pragma endregion