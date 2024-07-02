// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Turret_Enemy_AIController.h"
#include "AI/AI_Pawn.h"

ATurret_Enemy_AIController::ATurret_Enemy_AIController()
{
	AI_Perception_Component = CreateDefaultSubobject<UTurret_AIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AI_Perception_Component);
}

void ATurret_Enemy_AIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AIPawn = Cast<AAI_Pawn>(InPawn);
    if (AIPawn)
    {
        RunBehaviorTree(AIPawn->Behavior_Tree_Asset);
    }
}

void ATurret_Enemy_AIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    const auto AimActor = AI_Perception_Component->Get_Closest_Enemy();
    SetFocus(AimActor);
}

AActor* ATurret_Enemy_AIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(Focus_On_Key_Name));
}
