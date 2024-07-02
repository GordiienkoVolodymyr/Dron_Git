#include "AI/Service/Fire_BTService.h"

UFire_BTService::UFire_BTService()
{
	NodeName = "Fire";
}

void UFire_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Black_Board = OwnerComp.GetBlackboardComponent();

    const bool Has_Aim = Black_Board && Black_Board->GetValueAsObject(Enemy_Actor_Key.SelectedKeyName);

    if (Controller)
    {
        UWeapon_Component* Weapon_Component = Controller->GetPawn()->GetComponentByClass<UWeapon_Component>();
        if (Weapon_Component)
        {
            Has_Aim ? Weapon_Component->Start_Fire() : Weapon_Component->Stop_Fire();
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}