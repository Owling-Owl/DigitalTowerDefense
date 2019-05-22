// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DigitalTDController.generated.h"

/**
 * 
 */

UCLASS()
class DIGITALTOWERDEFENSE_API ADigitalTDController : public APlayerController
{
	GENERATED_BODY()
public:
	ADigitalTDController();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Ref")
	float CamMoveScreenRef = 30.0f;
	FVector2D CameraMove();
	int32 ViewportSizeX, ViewportSizeY;
	float MouseX, MouseY;
};
