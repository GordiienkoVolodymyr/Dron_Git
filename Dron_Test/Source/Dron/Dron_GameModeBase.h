// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player/Dron_Pawn.h"
#include "Player/Dron_PlayerController.h"
#include "UI/Game_HUD.h"
#include "Dron_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API ADron_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ADron_GameModeBase();
};
