// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AI_Pawn.h"
#include "Weapon/Player_Weapon.h"
#include "AI/Turret_Enemy_AIController.h"
#include "AI_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API AAI_Weapon : public APlayer_Weapon
{
	GENERATED_BODY()
	
public:
	virtual bool Get_Trace_Data(FVector& TraceStart, FVector& TraceEnd) const override;

};
