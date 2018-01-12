// Fill out your copyright notice in the Description page of Project Settings.

#include "DynaCharacter.h"
#include "Kismet/GameplayStatics.h"


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

	PlayerInputComponent->BindAxis("MoveForwardFirst", this, &ADynaCharacter::FirstCharMoveForward);
	PlayerInputComponent->BindAxis("MoveRightFirst", this, &ADynaCharacter::FirstCharMoveRight);

	PlayerInputComponent->BindAxis("MoveForwardSecond", this, &ADynaCharacter::SecondCharMoveForward);
	PlayerInputComponent->BindAxis("MoveRightSecond", this, &ADynaCharacter::SecondCharMoveRight);


	PlayerInputComponent->BindAction("SpawnBombFirst", EInputEvent::IE_Pressed, this, &ADynaCharacter::SpawnBombFirstCharacter);
	PlayerInputComponent->BindAction("SpawnBombSecond", EInputEvent::IE_Pressed, this, &ADynaCharacter::SpawnBombSecondCharacter);
}

float ADynaCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, "I'm Dead");
	bIsDead = true;
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

#pragma region Movement

void ADynaCharacter::FirstCharMoveForward(float Value)
{
	if (IAmSecondCharacter)
		return;

	MoveForward(Value);
}

void ADynaCharacter::FirstCharMoveRight(float Value)
{
	if (IAmSecondCharacter)
		return;

	MoveRight(Value);
}

void ADynaCharacter::SecondCharMoveForward(float Value)
{
	if(SecondCharacter)
		SecondCharacter->MoveForward(Value);
}

void ADynaCharacter::SecondCharMoveRight(float Value)
{
	if(SecondCharacter)
		SecondCharacter->MoveRight(Value);
}

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

#pragma region Weapon

void ADynaCharacter::SpawnBombFirstCharacter()
{
	if (IAmSecondCharacter)
		return;

	SpawnBomb();
}

void ADynaCharacter::SpawnBombSecondCharacter()
{
	if (SecondCharacter)
		SecondCharacter->SpawnBomb();
}

void ADynaCharacter::SpawnBomb()
{
	if (NumberOfBomb <= 0)
		return;

	FTransform Tr;
	Tr.SetLocation(GetActorLocation());
	ABomb* NewBomb = GetWorld()->SpawnActorDeferred<ABomb>(BombClassTemplate,Tr, this, this);
	if (NewBomb)
		UGameplayStatics::FinishSpawningActor(NewBomb, Tr);

	NumberOfBomb -= 1;
}

void ADynaCharacter::IncreaseBombCount()
{
	NumberOfBomb += 1;
}

#pragma endregion

