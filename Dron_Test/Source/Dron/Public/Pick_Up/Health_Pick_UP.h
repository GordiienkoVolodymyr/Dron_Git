// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pick_Up/Pick_UP.h"
#include "Components/Health_Component.h"
#include "Health_Pick_UP.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API AHealth_Pick_UP : public APick_UP
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
	float Health_Amount = 60.0f;

private:
	virtual bool Give_Pickup_To(APawn* Pawn) override;
};
