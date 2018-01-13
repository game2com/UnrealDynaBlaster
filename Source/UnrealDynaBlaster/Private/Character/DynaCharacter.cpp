// Fill out your copyright notice in the Description page of Project Settings.

#include "DynaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	PlayerInputComponent->BindAction("DetonatorFirst", EInputEvent::IE_Pressed, this, &ADynaCharacter::DetonatorBombFirstCharacter);
	PlayerInputComponent->BindAction("DetonatorSecond", EInputEvent::IE_Pressed, this, &ADynaCharacter::DetonatorBombSecondCharacter);
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
	if (bIsDead)
		return;

	FVector MoveVector = FVector(1, 0, 0);
	AddMovementInput(MoveVector * Value);
}

void ADynaCharacter::MoveRight(float Value)
{
	if (bIsDead)
		return;

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

void ADynaCharacter::DetonatorBombFirstCharacter()
{
	if (IAmSecondCharacter)
		return;

	DetonatorBomb();
}

void ADynaCharacter::DetonatorBombSecondCharacter()
{
	if (SecondCharacter)
		SecondCharacter->DetonatorBomb();
}

void ADynaCharacter::SpawnBomb()
{
	if (bIsDead)
		return;

	if (NumberOfBomb <= 0)
		return;

	if (bCanDetonatorBomb && CurrentBomb != nullptr)
		return;

	FTransform Tr;
	FVector SnapLocation = GetActorLocation();
	SnapLocation.Y /= 100.0f;
	SnapLocation.Y = FMath::RoundToFloat(SnapLocation.Y);
	SnapLocation.Y *= 100.0f;

	SnapLocation.X /= 100.0f;
	SnapLocation.X = FMath::RoundToFloat(SnapLocation.X);
	SnapLocation.X *= 100.0f;
	Tr.SetLocation(SnapLocation);
	ABomb* NewBomb = GetWorld()->SpawnActorDeferred<ABomb>(BombClassTemplate,Tr, this, this);
	if (NewBomb)
	{
		NewBomb->ExplosionLength = BombFireLength;
		NewBomb->bCanRemoteControlBomb = bCanDetonatorBomb;
		UGameplayStatics::FinishSpawningActor(NewBomb, Tr);
		CurrentBomb = NewBomb;
	}

	NumberOfBomb -= 1;
}

void ADynaCharacter::DetonatorBomb()
{
	if (bCanDetonatorBomb == false)
		return;

	if (CurrentBomb)
	{
		CurrentBomb->Explode();
	}
}

void ADynaCharacter::IncreaseBombCount()
{
	NumberOfBomb += 1;
	CurrentBomb = nullptr;
}

void ADynaCharacter::IncreaseNumberOfBomb()
{
	NumberOfBomb++;
}

void ADynaCharacter::IncreaseLengthOfBombFire()
{
	BombFireLength++;
}

void ADynaCharacter::IncreaseWalkSpeed()
{
	if (GetCharacterMovement())
		GetCharacterMovement()->MaxWalkSpeed += 25.0f;
}

void ADynaCharacter::SetCanDetonatorBomb()
{
	bCanDetonatorBomb = true;
}

#pragma endregion

