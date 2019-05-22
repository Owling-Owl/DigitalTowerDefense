// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicTower.h"
#include "Classes/Components/SphereComponent.h"
#include "TimerManager.h"
#include "Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ABasicTower::ABasicTower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	RootComponent = TowerMesh;
	AttackArea = CreateDefaultSubobject<USphereComponent>(TEXT("AttackArea"));
	AttackArea->SetupAttachment(RootComponent);
	AttackArea->SetSphereRadius(1000.0f);
	FireEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Fire"));

	DetectPeriod = 5.0f;

	Damage = 600.0f;
}

// Called when the game starts or when spawned
void ABasicTower::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DetectTimer, this, &ABasicTower::Detecting, 5.0f, true, DetectPeriod);
}

// Called every frame
void ABasicTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicTower::Detecting()
{
	TArray<AActor*> AllTargets;
	AttackArea->GetOverlappingActors(AllTargets);
	for (int32 iTargets = 0; iTargets < AllTargets.Num(); iTargets++)
	{
		/*AAIPatrol* const Enemy = Cast<AAIPatrol>(AllTargets[iTargets]);
		if (Enemy && !IsPendingKill())
		{
			if (Enemy->GetCurrentHealth() > 0)
			{
				Enemy->UpdateHealth(-Damage);
				ABasicTower::Fire(Enemy->GetActorLocation());
				Enemy->IsAlive();
			}
		}*/
	}
}

void ABasicTower::Fire(FVector Location)
{
	UWorld* const World = GetWorld();
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, FString::SanitizeFloat(Location.X) + FString::FString(" ") + FString::SanitizeFloat(Location.Y) + FString::FString(" ") + FString::SanitizeFloat(Location.Z));
	UGameplayStatics::SpawnEmitterAtLocation(World, FireEffect, Location, FRotator(0, 0, 0), FVector(1, 1, 1), false);
}