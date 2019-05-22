// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParticleDefinitions.h"
#include "BasicTower.generated.h"

UCLASS()
class DIGITALTOWERDEFENSE_API ABasicTower : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasicTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle DetectTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower")
		float DetectPeriod;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower")
		float Damage;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class UStaticMeshComponent* GetMesh()const { return TowerMesh; };
	UFUNCTION(BlueprintCallable, Category = "Tower")
		void Detecting();
	//
	UFUNCTION(BlueprintCallable, Category = "Tower")
		void Fire(FVector Location);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TowerMesh;

	//detecting area 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* AttackArea;

	//particle system 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower", meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* FireEffect;


};
