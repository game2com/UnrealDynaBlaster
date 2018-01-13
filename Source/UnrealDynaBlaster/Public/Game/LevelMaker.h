// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.h"
#include "Components/BillboardComponent.h"
#include "LevelMaker.generated.h"



USTRUCT(BlueprintType)
struct FTileInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABlock* BlockActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Column;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Row;

	void SetDefault(ABlock* NewMesh, int32 NewCol, int32 NewRow)
	{
		BlockActor = NewMesh;
		Column = NewCol;
		Row = NewRow;
	}
};



UCLASS()
class UNREALDYNABLASTER_API ALevelMaker : public AActor
{
	GENERATED_BODY()
	
#pragma region Main
public:	
	// Sets default values for this actor's properties
	ALevelMaker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region Componenets
protected:
	UPROPERTY(EditDefaultsOnly, Category = Components)
		USceneComponent* SceneRootComp;

	UPROPERTY(EditDefaultsOnly, Category = Components)
		UBillboardComponent* IconComp;


#pragma endregion
	
#pragma region Level Maker Controller
protected:
	UPROPERTY(EditAnywhere, Category = Controller)
		int32 NumberOfColumn = 11;

	UPROPERTY(EditAnywhere, Category = Controller)
		int32 NumberOfRow = 13;

	UPROPERTY(EditAnywhere, Category = "Controller|Ground")
		UStaticMesh* PlaneMesh;

	UPROPERTY(EditAnywhere, Category = "Controller|Ground")
		UMaterialInterface* PlaneMaterial;

	UPROPERTY(EditAnywhere, Category = "Controller|Ground")
		float SizeOfBlock = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Controller|Ground")
		TArray<UStaticMeshComponent*> SpawnedGroundPlane;

	UPROPERTY(EditAnywhere, Category = "Controller|Block")
		TSubclassOf<ABlock> BlockMesh;

	UPROPERTY(VisibleAnywhere, Category = "Controller|Block")
		TArray<FTileInfo> SpawnedBlock;

	UPROPERTY(VisibleAnywhere, Category = "Controller|Fence")
		TArray<FTileInfo> SpawnedFence;

	UPROPERTY(EditAnywhere, Category = "Controller|Brick")
		TSubclassOf<ABlock> BrickMesh;

	UPROPERTY(EditAnywhere, Category = "Controller|Brick", meta = (UIMin = "0.0", UIMax = "1.0"))
		float BricksCrowd = 0.5f;

	UPROPERTY(VisibleAnywhere, Category = "Controller|Brick")
		TArray<FTileInfo> SpawnedBricks;



	UFUNCTION(BlueprintCallable, Category = LevelMaker)
	void MakeProceduralMap(FVector2D& FirstPlayerPos, FVector2D& SecondPlayerPos);

	void ClearSpanwedTiles();

	void MakeGround(int32 ColNum, int32 RowNum);

	void MakeIndestructibleBlock(int32 ColNum, int32 RowNum);

	void SpawnDestructibleBricks(int32 ColNum, int32 RowNum);

	void MakeFence();

	UStaticMeshComponent* SpawnMeshComponent(UStaticMesh* NewMesh, FVector Position, UMaterialInterface* Material);

	ABlock* SpawnBlock(TSubclassOf<ABlock> ThisBlockType, FVector Position);
#pragma endregion
};
