// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/Turret_AIPerceptionComponent.h"
#include "Turret_Enemy_AIController.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API ATurret_Enemy_AIController : public AAIController
{
	GENERATED_BODY()
	

public:
    ATurret_Enemy_AIController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    UTurret_AIPerceptionComponent* AI_Perception_Component;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    FName Focus_On_Key_Name = "EnemyActor";

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

private:
    AActor* GetFocusOnActor() const;
};
