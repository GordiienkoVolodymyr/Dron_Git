#include "AI/Service/Find_BTService.h"

UFind_BTService::UFind_BTService()
{
    NodeName = "Find Enemy";
}

void UFind_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
    if (BlackBoard)
    {
        AAIController* Controller = OwnerComp.GetAIOwner();
        UTurret_AIPerceptionComponent* AIPerception_Component = Controller->GetComponentByClass<UTurret_AIPerceptionComponent>();
        if (AIPerception_Component)
        {
            BlackBoard->SetValueAsObject(Enemy_Actor_Key.SelectedKeyName, AIPerception_Component->Get_Closest_Enemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
