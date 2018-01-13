// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

class ADynaCharacter;
UCLASS()
class UNREALDYNABLASTER_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bExploded = false;
	UPROPERTY(EditAnywhere, Category = Component)
		UStaticMeshComponent* BombMesh;

	UPROPERTY(EditDefaultsOnly, Category = Controller)
		float TimeToExplode = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = Controller)
		UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = Controller)
		int32 ExplosionLength = 2;

	FTimerHandle TimerHandle_Explode;
	UFUNCTION(BlueprintCallable, Category = Controller)
	void Explode();
	
	UFUNCTION(BlueprintImplementableEvent)
	void AfterExplosion();

	UPROPERTY(BlueprintReadOnly, Category = Controller)
	bool bCanRemoteControlBomb = false;
};
