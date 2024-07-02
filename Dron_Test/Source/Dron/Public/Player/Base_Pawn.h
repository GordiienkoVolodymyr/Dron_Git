// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/Health_Component.h"
#include "Components/Weapon_Component.h"
#include "GameFramework/Pawn.h"
#include "Base_Pawn.generated.h"

UCLASS()
class DRON_API ABase_Pawn : public APawn
{
	GENERATED_BODY()

public:
	ABase_Pawn();

	virtual void Tick(float DeltaTime) override;

	USkeletalMeshComponent* Get_Mesh() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* Box_Colision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* Skeletal_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UHealth_Component* Health_Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UWeapon_Component* Weapon_Component;

	virtual void On_Health_Changed(float Health, float HealthDelta);
	virtual void On_Death();
};
