// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelMaker.h"
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

void ALevelMaker::MakeProceduralMap(FVector2D& FirstPlayerPos, FVector2D& SecondPlayerPos)
{
	/*Clear Previous*/
	ClearSpanwedTiles();

	/*Add New*/
	for (int32 Col = 0; Col < NumberOfColumn; Col++)
	{
		for (int32 Row = 0; Row < NumberOfRow; Row++)
		{
			if (Col == 0, Row == 0)
				SecondPlayerPos = FVector2D(0, 0);

			if (Col == NumberOfColumn - 1 && Row == NumberOfRow - 1)
				FirstPlayerPos = FVector2D(Col * SizeOfBlock, Row * SizeOfBlock);

			MakeGround(Col, Row);
			MakeIndestructibleBlock(Col, Row);
			SpawnDestructibleBricks(Col, Row);
		}
	}
	MakeFence();
}

void ALevelMaker::ClearSpanwedTiles()
{
	/*Clear previous ground*/
	if (SpawnedGroundPlane.Num() > 0)
	{
		for (UStaticMeshComponent* ThisTile : SpawnedGroundPlane)
		{
			ThisTile->DestroyComponent(true);
		}
	}
	SpawnedGroundPlane.Empty();

	/*Clear previous Block*/
	if (SpawnedBlock.Num() > 0)
	{
		for (FTileInfo ThisTile : SpawnedBlock)
		{
			if (ThisTile.BlockActor->IsValidLowLevel())
				ThisTile.BlockActor->Destroy();
			ThisTile.Column = 0;
			ThisTile.Row = 0;
		}
	}
	SpawnedBlock.Empty();

	//Clear Previous Fence
	if (SpawnedFence.Num() > 0)
	{
		for (FTileInfo ThisTile : SpawnedFence)
		{
			if (ThisTile.BlockActor->IsValidLowLevel())
				ThisTile.BlockActor->Destroy();
			ThisTile.Column = 0;
			ThisTile.Row = 0;
		}
	}
	SpawnedFence.Empty();

	//Clear Previous SpawnedBricks
	if (SpawnedBricks.Num() > 0)
	{
		for (FTileInfo ThisTile : SpawnedBricks)
		{
			if (ThisTile.BlockActor->IsValidLowLevel())
				ThisTile.BlockActor->Destroy();
			ThisTile.Column = 0;
			ThisTile.Row = 0;
		}
	}
	SpawnedBricks.Empty();
}

void ALevelMaker::MakeGround(int32 ColNum, int32 RowNum)
{
	FVector Loc = FVector::ZeroVector;
	Loc.Y = RowNum * SizeOfBlock;
	Loc.X = ColNum * SizeOfBlock;

	UStaticMeshComponent* NewMesh = SpawnMeshComponent(PlaneMesh, Loc, PlaneMaterial);

	/*Store in array*/
	SpawnedGroundPlane.Add(NewMesh);
}

void ALevelMaker::MakeIndestructibleBlock(int32 ColNum, int32 RowNum)
{
	if (ColNum == 0 || ColNum % 2 == 0)
		return;

	if (RowNum == 0 || RowNum % 2 == 0)
		return;


	FVector Loc = FVector::ZeroVector;
	Loc.Y = RowNum * SizeOfBlock;
	Loc.X = ColNum * SizeOfBlock;

	ABlock* NewBlock = SpawnBlock(BlockMesh, Loc);

	/*Store in array*/
	FTileInfo NewTile = FTileInfo();
	NewTile.SetDefault(NewBlock, ColNum, RowNum);
	SpawnedBlock.Add(NewTile);
	
}

void ALevelMaker::SpawnDestructibleBricks(int32 ColNum, int32 RowNum)
{
	//if (ColNum == 0 || ColNum % 2 == 0)
		//return;

	if (ColNum % 2 != 0 && RowNum % 2 != 0)
		return;

	if ((ColNum == 0 || ColNum == 1) && (RowNum == 0 || RowNum == 1))
		return;

	if ((ColNum == NumberOfColumn - 1 || ColNum == NumberOfColumn - 2) && (RowNum == NumberOfRow - 1 || RowNum == NumberOfRow - 2))
		return;

	if (FMath::FRand() > BricksCrowd)
		return;

	FVector Loc = FVector::ZeroVector;
	Loc.Y = RowNum * SizeOfBlock;
	Loc.X = ColNum * SizeOfBlock;

	ABlock* NewBlock = SpawnBlock(BrickMesh, Loc);

	/*Store in array*/
	FTileInfo NewTile = FTileInfo();
	NewTile.SetDefault(NewBlock, ColNum, RowNum);
	SpawnedBricks.Add(NewTile);
}

void ALevelMaker::MakeFence()
{
	for (int32 i = -1; i < NumberOfColumn + 1; i++)
	{
		for (int32 j = -1; j < NumberOfRow + 1; j++)
		{

			if ((i > -1 && i < NumberOfColumn) && (j > -1 && j < NumberOfRow))
				continue;

			FVector Loc = FVector::ZeroVector;
			Loc.Y = j * SizeOfBlock;
			Loc.X = i * SizeOfBlock;

			ABlock* NewFenceBlock = SpawnBlock(BlockMesh, Loc);

			FTileInfo NewTile = FTileInfo();
			NewTile.SetDefault(NewFenceBlock, -1, j);
			SpawnedFence.Add(NewTile);
		}
	}
}

UStaticMeshComponent* ALevelMaker::SpawnMeshComponent(UStaticMesh* NewMesh, FVector Position, UMaterialInterface* Material)
{

	UStaticMeshComponent* CurrentMeshComp = NewObject<UStaticMeshComponent>(this);
	if (CurrentMeshComp)
	{
		CurrentMeshComp->RegisterComponentWithWorld(GetWorld());
		FAttachmentTransformRules ATR = FAttachmentTransformRules(EAttachmentRule::KeepWorld, false);
		CurrentMeshComp->AttachToComponent(RootComponent, ATR);
		AddOwnedComponent(CurrentMeshComp);
		CurrentMeshComp->SetWorldLocation(Position);
		CurrentMeshComp->SetStaticMesh(NewMesh);
		CurrentMeshComp->SetMaterial(0, Material);
	}

	return CurrentMeshComp;
}

ABlock* ALevelMaker::SpawnBlock(TSubclassOf<ABlock> ThisBlockType, FVector Position)
{
	if (ThisBlockType == nullptr)
		return nullptr;

	FTransform Tr;
	ABlock* TempBlock = GetWorld()->SpawnActor<ABlock>(ThisBlockType, Tr);
	if (TempBlock)
	{
		TempBlock->SetActorLocation(Position);
	}

	return TempBlock;
}

#pragma endregion