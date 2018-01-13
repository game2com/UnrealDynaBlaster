// Fill out your copyright notice in the Description page of Project Settings.

#include "Block.h"


// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>("Block Mesh Component");
	RootComponent = BlockMesh;
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABlock::CanSpawnPickuableByChance()
{
	return FMath::FRand() < ChanceToHavePickableActor ? true : false;
}

TEnumAsByte<SpawnType> ABlock::GetRandomSpawnType()
{
	return TEnumAsByte<SpawnType>(FMath::RandRange(0, (int32)SpawnType::SP_FireIncrease));
}
