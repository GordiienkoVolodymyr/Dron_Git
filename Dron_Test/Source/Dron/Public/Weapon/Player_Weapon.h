// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Base_Weapon.h"
#include "Weapon/Missile_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Player_Weapon.generated.h"


UCLASS()
class DRON_API APlayer_Weapon : public ABase_Weapon
{
	GENERATED_BODY()
public:
	APlayer_Weapon();

	virtual void Start_Fire() override;

protected:

	virtual void Make_Shot() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AMissile_Projectile> Missile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FVector Missile_Spawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Damage_Radius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Full_Damege;
};
