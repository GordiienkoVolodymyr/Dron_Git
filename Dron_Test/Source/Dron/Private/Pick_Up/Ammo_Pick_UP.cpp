// Fill out your copyright notice in the Description page of Project Settings.


#include "Pick_Up/Ammo_Pick_UP.h"

bool AAmmo_Pick_UP::Give_Pickup_To(APawn* Pawn)
{
    if (!Pawn) return false;

    const auto Health_Component = Pawn->GetComponentByClass<UHealth_Component>();
    if (!Health_Component || Health_Component->Is_Dead()) return false;

    const auto Weapon_Component = Pawn->GetComponentByClass<UWeapon_Component>();
    if (!Weapon_Component) return false;

    return Weapon_Component->To_Add_Ammo(Weapon_Type, ClipsAmount);
}
