// Fill out your copyright notice in the Description page of Project Settings.


#include "DigitalTDController.h"
#include "CameraPawn.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

ADigitalTDController::ADigitalTDController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void ADigitalTDController::BeginPlay()
{
	Super::BeginPlay();
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Xsize %d \nYsize %d"),ViewportSizeX,ViewportSizeY));
}

void ADigitalTDController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CameraMove().X||CameraMove().Y)
	{
		ACameraPawn* const Mycam = Cast<ACameraPawn>(GetPawn());
		Mycam->MoveX(CameraMove().X);
		Mycam->MoveY(CameraMove().Y);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,FString::Printf( TEXT("LocationX = %f\nLocationY = %f"),GetPawn()->GetActorLocation().X, GetPawn()->GetActorLocation().Y));
	}
}

FVector2D ADigitalTDController::CameraMove()
{
	//initialize
	FVector2D Dir = {0,0};
	GetMousePosition(MouseX, MouseY);
	if (MouseX <= CamMoveScreenRef)//up
		Dir.Y = -1.0f;
	else if (ViewportSizeX - MouseX <= CamMoveScreenRef)//down
		Dir.Y = 1.0f;
	if (MouseY <= CamMoveScreenRef)//right
		Dir.X = 1.0f;
	else if (ViewportSizeY - MouseY <= CamMoveScreenRef)//left
		Dir.X = -1.0f;
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Xsize %f \nYsize %f"), MouseX, MouseY));
	if (Dir.X && Dir.Y)
	{
		Dir.X *= 0.707f;
		Dir.Y *= 0.707f;
	}
	return FVector2D(Dir);
}

