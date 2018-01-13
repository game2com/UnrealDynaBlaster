// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "Kismet/GameplayStatics.h"
#include "DynaCharacter.h"
#include "DrawDebugHelpers.h"
#include "Game/Block.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ABomb::ABomb()
{

	PrimaryActorTick.bCanEverTick = false;

	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomb Mesh Component"));
	RootComponent = BombMesh;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
	//GetWorldTimerManager().SetTimer(TimerHandle_Explode, this, &ABomb::Explode, TimeToExplode, false);
	//Explode();
}

const bool ABomb::GameIsRuning()
{
	bool ContinueGame = true;
	for (auto FConstPawnIterator = GetWorld()->GetPawnIterator(); FConstPawnIterator; ++FConstPawnIterator)
	{
		APawn* ThisPawn = *FConstPawnIterator;

		if (Cast<ADynaCharacter>(ThisPawn))
		{
			if (Cast<ADynaCharacter>(ThisPawn)->bIsDead == true)
			{
				ContinueGame = false;
			}
		}
	}

	return ContinueGame;
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::Explode()
{
	if (GameIsRuning() == false)
		return;

	if (bExploded)
		return;

	bExploded = true;

	if (GetOwner() && Cast<ADynaCharacter>(GetOwner()))
		Cast<ADynaCharacter>(GetOwner())->IncreaseBombCount();

	if (ExplosionEffect && GetWorld())
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), FRotator(), true);

	FHitResult HitInfo;
	FCollisionQueryParams CQP = FCollisionQueryParams();
	CQP.AddIgnoredActor(this);

	FVector EndForward = GetActorLocation() + FVector(50 * ExplosionLength, 0, 0);
	FVector EndBackward = GetActorLocation() + FVector(50 * -ExplosionLength, 0, 0);
	FVector EndRight = GetActorLocation() + FVector(0, 50 * ExplosionLength, 0);
	FVector EndLeft = GetActorLocation() + FVector(0, 50 * -ExplosionLength, 0);

	 for (int i = 0; i < 4; i++)
	 {
		 FVector DesireEnd = EndForward;
		 if (i == 1) DesireEnd = EndBackward;
		 else if (i == 2) DesireEnd = EndLeft;
		 else if (i == 3) DesireEnd = EndRight;

		// DrawDebugLine(GetWorld(), GetActorLocation(), DesireEnd, FColor::Red, true, 1);


		 if (GetWorld()->LineTraceSingleByChannel(HitInfo, GetActorLocation(), DesireEnd, ECC_WorldStatic, CQP))
		 {
			if (HitInfo.GetActor())
			{
				SpawnLineFire(HitInfo.ImpactPoint);

				if (Cast<ABlock>(HitInfo.GetActor()))
				{
					Cast<ABlock>(HitInfo.GetActor())->OnBlockExplosion();
				}
				else if (Cast<ADynaCharacter>(HitInfo.GetActor()))
				{
					TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
					FDamageEvent DamageEvent(ValidDamageTypeClass);

					Cast<ADynaCharacter>(HitInfo.GetActor())->TakeDamage(10, DamageEvent, GetOwner()->GetInstigatorController(), this);
				}
				else if (Cast<ABomb>(HitInfo.GetActor()))
				{
					Cast<ABomb>(HitInfo.GetActor())->Explode();
				}
			}
		 }
		 else
		 {
			 SpawnLineFire(DesireEnd);
		 }
	 }

	AfterExplosion();
}

void ABomb::SpawnLineFire(FVector EndPos)
{
	if (ExplosionLine && GetWorld() && PointHelper)
	{
		UParticleSystemComponent* PS = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionLine, GetActorLocation(), FRotator(), true);
		if (PS)
		{
			PS->SetVectorParameter("BeamSource", GetActorLocation());

			AActor* PointToTarget = GetWorld()->SpawnActor<AActor>(PointHelper, EndPos, FRotator());
			if (PointToTarget)
				PS->SetActorParameter("BeamTarget", PointToTarget);
		}
	}
}

