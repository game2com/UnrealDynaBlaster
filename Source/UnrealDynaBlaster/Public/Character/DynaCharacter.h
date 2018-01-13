// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bomb.h"
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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Main)
		ADynaCharacter* SecondCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Main)
		bool IAmSecondCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Main)
		float Score = 0.0f;

protected:
	void SaveCurrentScore();
	void LoadPreviousScore();

	FTimerHandle TimerHandle_AddScoreAfterDead;
	UFUNCTION()
	void AddScoreAfterDead();
	
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnWinUI();

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnDrawUI();

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

public:
	bool bLockKeys;

#pragma endregion
	
#pragma region Weapon
protected:

	UPROPERTY(EditAnywhere, Category = Weapon)
		TSubclassOf<ABomb> BombClassTemplate;

	UPROPERTY(EditAnywhere, Category = Weapon)
		int32 NumberOfBomb = 1;

	UPROPERTY(EditAnywhere, Category = Weapon)
		int32 BombFireLength = 2;

	UPROPERTY(EditAnywhere, Category = Weapon)
		bool bCanDetonatorBomb = false;

	ABomb* CurrentBomb = nullptr;

	UFUNCTION()
	void SpawnBombFirstCharacter();

	UFUNCTION()
	void SpawnBombSecondCharacter();
	

	UFUNCTION()
		void DetonatorBombFirstCharacter();

	UFUNCTION()
		void DetonatorBombSecondCharacter();

	void SpawnBomb();
	void DetonatorBomb();
public:

	void IncreaseBombCount();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void IncreaseNumberOfBomb();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void IncreaseLengthOfBombFire();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void IncreaseWalkSpeed();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetCanDetonatorBomb();

	UFUNCTION(BlueprintPure, Category = Weapon)
		inline int32 GetNumberOfBomb() { return NumberOfBomb; }
#pragma endregion

#pragma region Timer
protected:
	UPROPERTY(EditAnywhere, Category = Timer)
		bool bDelegateTimer = false;

	UPROPERTY(EditAnywhere, Category = Timer)
		int32 MaxTime = 120;

	int32 Timer = MaxTime;

	void RunTimer();

	FTimerHandle TimerHandle_TimerSubtract;
	UFUNCTION()
	void TimerSubtract();
public:

	UFUNCTION(BlueprintPure, Category = Timer)
		int32 GetTimer() { return bDelegateTimer ? Timer : 0; }
#pragma endregion
};
