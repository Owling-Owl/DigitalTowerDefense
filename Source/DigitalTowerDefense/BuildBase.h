// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildBase.generated.h"

UCLASS()
class DIGITALTOWERDEFENSE_API ABuildBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildBase();
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Mesh;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bEnableBuild;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ABasicTower> WhatToSpawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "C Function ActorOnclick")
	void OnClick(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);
};
