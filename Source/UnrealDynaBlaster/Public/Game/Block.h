// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UENUM(BlueprintType)
enum BlockType
{
	BT_Block,
	BT_Brick,
};

UCLASS()
class UNREALDYNABLASTER_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditDefaultsOnly, Category = Components)
		UStaticMeshComponent* BlockMesh;
	
public:
	UPROPERTY(EditAnywhere, Category = Controller)
		TEnumAsByte<BlockType> _BlockType;

	inline UStaticMeshComponent* GetBlockMeshComponent() { return BlockMesh; }

public:

	UFUNCTION(BlueprintImplementableEvent, Category = Controller)
	void OnBlockExplosion();
};
