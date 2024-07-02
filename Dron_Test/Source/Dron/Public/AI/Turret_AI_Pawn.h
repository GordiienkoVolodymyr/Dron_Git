// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AI_Pawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/Weapon_Component.h"
#include "Turret_AI_Pawn.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API ATurret_AI_Pawn : public AAI_Pawn
{
	GENERATED_BODY()
	
public:
    ATurret_AI_Pawn();

protected:

    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent* Scene_Component;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* Stand_Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
    float Min_Pitch;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
    float Max_Pitch;

private:
    void Rotate_Towards_Focus_Actor(const AActor* FocusActor);
};
