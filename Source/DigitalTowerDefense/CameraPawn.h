// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DigitalTDController.h"
#include "CameraPawn.generated.h"

UCLASS()
class DIGITALTOWERDEFENSE_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle DelayTimer;

	bool bIsActorRotationActive = true;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere,Category="Ref")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere,Category = "Ref")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = "Ref")
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Zoom")
	float ZoomUnit;
	int CamOrthoWidth;
	int ZoomVelocity;

	UPROPERTY(EditDefaultsOnly, Category = Curve)
	UCurveFloat* Curve;

	UPROPERTY(EditAnywhere, Category = "Ref")
	float Speed = 10.0f;

	FVector CurrentVelocity;

	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Zoom")
	void ZoomIn();
	UFUNCTION(BlueprintCallable, Category = "Zoom")
	void ZoomOut();

	UFUNCTION(BlueprintCallable, Category = "CamView")
	void CamRotation(float AxisValue);
	UFUNCTION(BlueprintCallable, Category = "CamView")
	void ToggleRotationActive();
	UFUNCTION(BlueprintCallable, Category = "CamView")
	void isCamRotationActive();
};
