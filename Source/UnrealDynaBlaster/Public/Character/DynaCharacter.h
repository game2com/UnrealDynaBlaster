// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DynaCharacter.generated.h"

UCLASS()
class UNREALDYNABLASTER_API ADynaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADynaCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Main)
		ADynaCharacter* SecondCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Main)
		bool IAmSecondCharacter;
#pragma region Movement
protected:

	UFUNCTION()
		void FirstCharMoveForward(float Value);
	UFUNCTION()
		void FirstCharMoveRight(float Value);

	UFUNCTION()
	void SecondCharMoveForward(float Value);
	UFUNCTION()
	void SecondCharMoveRight(float Value);

	void MoveForward(float Value);

	void MoveRight(float Value);


#pragma endregion
	
};
