// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/Turret_AIPerceptionComponent.h"
#include "Find_BTService.generated.h"

UCLASS()
class DRON_API UFind_BTService : public UBTService
{
	GENERATED_BODY()

public:
	UFind_BTService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector Enemy_Actor_Key;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};
