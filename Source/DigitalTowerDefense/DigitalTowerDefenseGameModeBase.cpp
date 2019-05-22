// Fill out your copyright notice in the Description page of Project Settings.

#include "DigitalTowerDefenseGameModeBase.h"
#include "DigitalTDController.h"
#include "CameraPawn.h"
ADigitalTowerDefenseGameModeBase::ADigitalTowerDefenseGameModeBase()
{
	DefaultPawnClass = ACameraPawn::StaticClass();
	PlayerControllerClass = ADigitalTDController::StaticClass();
}
