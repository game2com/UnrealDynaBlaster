// Fill out your copyright notice in the Description page of Project Settings.

#include "DynaCharacter.h"



ADynaCharacter::ADynaCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ADynaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADynaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADynaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADynaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADynaCharacter::MoveRight);
}

#pragma region Movement
void ADynaCharacter::MoveForward(float Value)
{
	FVector MoveVector = FVector(1, 0, 0);
	AddMovementInput(MoveVector * Value);
}

void ADynaCharacter::MoveRight(float Value)
{

	FVector MoveVector = FVector(0, 1, 0);
	AddMovementInput(MoveVector * Value);
}
#pragma endregion

