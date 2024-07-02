#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/Weapon_Component.h"
#include "Fire_BTService.generated.h"


UCLASS()
class DRON_API UFire_BTService : public UBTService
{
	GENERATED_BODY()
	
public:
	UFire_BTService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector Enemy_Actor_Key;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
