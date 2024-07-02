// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Base_Pawn.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Health_Component.h"
#include "Logging/LogMacros.h"
#include "AI/Turret_Enemy_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Net/Core/Connection/NetResult.h"
#include "UI/Health_UserWidget.h"
#include "AI_Pawn.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API AAI_Pawn : public ABase_Pawn
{
	GENERATED_BODY()
public:
    AAI_Pawn();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* Behavior_Tree_Asset;

    ATurret_Enemy_AIController* Get_AI_Controller() const;

    virtual void Tick(float DeltaSeconds) override;

protected:
     UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
     UWidgetComponent* HealthWidgetComponent;

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
     float HealthVisibilityDistance = 1000.0f;

    UPROPERTY()
    ATurret_Enemy_AIController* AI_Controller;

    void Set_AI_Controller();

    virtual void BeginPlay() override;

    virtual void On_Death() override;
    virtual void On_Health_Changed(float Health, float HealthDelta) override;

private:
    void Update_Health_Widget_Visibility();
};
