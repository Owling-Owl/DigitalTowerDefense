// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildBase.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "BasicTower.h"
#include "Engine/Classes/Engine/Engine.h"

// Sets default values
ABuildBase::ABuildBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	bEnableBuild = true;
	Mesh->OnClicked.AddDynamic(this, &ABuildBase::OnClick);
	
}

// Called when the game starts or when spawned
void ABuildBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABuildBase::OnClick(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, TEXT("Test"));
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	SpawnParam.Instigator = Instigator;
	FVector WhereToSpawn = GetActorLocation();
	WhereToSpawn.Z += 5;
	if(bEnableBuild)
	GetWorld()->SpawnActor<ABasicTower>(WhatToSpawn,WhereToSpawn,FRotator(0.0,0.0,0.0),SpawnParam);
	bEnableBuild = false;
}

