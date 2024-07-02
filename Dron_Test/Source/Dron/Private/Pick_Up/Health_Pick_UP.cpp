#include "Pick_Up/Health_Pick_UP.h"

bool AHealth_Pick_UP::Give_Pickup_To(APawn* Pawn)
{
    if (!Pawn) return false;

    const auto Health_Component = Pawn->GetComponentByClass<UHealth_Component>();
    if (!Health_Component || Health_Component->Is_Dead()) return false;

    return Health_Component->Add_health(Health_Amount);
}
