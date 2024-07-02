// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Turret_AIPerceptionComponent.h"

AActor* UTurret_AIPerceptionComponent::Get_Closest_Enemy() const
{
    TArray<AActor*> Perceive_Actors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Perceive_Actors);
    if (Perceive_Actors.Num() == 0)
    {
        return nullptr;
    }
    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller)
    {
        return nullptr;
    }

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
    {
        return nullptr;
    }

    float Best_Distance = MAX_FLT;
    AActor* Best_Pawn = nullptr;

    for (const auto Perceive_Actor : Perceive_Actors)
    {
        const auto Health_Component = Perceive_Actor->GetComponentByClass<UHealth_Component>();

        if (Health_Component && !Health_Component->Is_Dead() && CastChecked<ADron_Pawn>(Perceive_Actor))
        {
            const auto Current_Distance = (Perceive_Actor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (Current_Distance < Best_Distance)
            {
                Best_Distance = Current_Distance;
                Best_Pawn = Perceive_Actor;
            }
        }
    }
    return Best_Pawn;
}
