// Fill out your copyright notice in the Description page of Project Settings.


#include "Dron_GameModeBase.h"

ADron_GameModeBase::ADron_GameModeBase()
{
	DefaultPawnClass = ADron_Pawn::StaticClass();
	PlayerControllerClass = ADron_PlayerController::StaticClass();
	HUDClass = AGame_HUD::StaticClass();
}
