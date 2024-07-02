// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Player/Dron_Pawn.h"
#include "Components/Health_Component.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Turret_AIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API UTurret_AIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	AActor* Get_Closest_Enemy() const;
};
