// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon/Base_Weapon.h"
#include "CoreMinimal.h"
#include "Pick_Up/Pick_UP.h"
#include "Components/Health_Component.h"
#include "Components/Weapon_Component.h"
#include "Ammo_Pick_UP.generated.h"



UCLASS()
class DRON_API AAmmo_Pick_UP : public APick_UP
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = 10.0))
    int64 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<ABase_Weapon> Weapon_Type;
private:
    virtual bool Give_Pickup_To(APawn* Pawn) override;

};
