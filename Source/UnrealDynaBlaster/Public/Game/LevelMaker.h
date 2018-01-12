// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelMaker.generated.h"

USTRUCT(BlueprintType)
struct FTileInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Column;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Row;

	void SetDefault(UStaticMeshComponent* NewMesh, int32 NewCol, int32 NewRow)
	{
		MeshComp = NewMesh;
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

	UPROPERTY(EditAnywhere, Category = Controller)
		UStaticMesh* PlaneMesh;

	UPROPERTY(EditAnywhere, Category = Controller)
		UMaterialInterface* PlaneMaterial;

	UPROPERTY(EditAnywhere, Category = Controller)
		float SizeOfBlock = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = Controller)
		TArray<FTileInfo> SpawnedGroundPlane;

	UFUNCTION(BlueprintCallable, Category = LevelMaker)
	void MakeGround();


	UStaticMeshComponent* SpawnMeshComponent(UStaticMesh* NewMesh, FVector Position, UMaterialInterface* Material);
#pragma endregion
};
