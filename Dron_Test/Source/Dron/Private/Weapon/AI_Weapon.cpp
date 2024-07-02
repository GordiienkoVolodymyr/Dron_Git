// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AI_Weapon.h"

bool AAI_Weapon::Get_Trace_Data(FVector& TraceStart, FVector& TraceEnd) const
{
    if (AAI_Pawn* AIPawn = Cast<AAI_Pawn>(GetOwner()))
    {
        if (ATurret_Enemy_AIController* AI_Controller = AIPawn->Get_AI_Controller())
        {

            TraceStart = Get_Muzzle_World_Location();
            if (AI_Controller->GetFocusActor())
            {
                const FVector Shoot_Direction = AI_Controller->GetFocusActor()->GetActorLocation();
                TraceEnd = Shoot_Direction;

                return true;
            }
        }
    }
    return false;
}
