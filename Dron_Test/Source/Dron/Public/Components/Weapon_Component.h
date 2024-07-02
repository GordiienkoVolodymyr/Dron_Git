// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon/Base_Weapon.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon_Component.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRON_API UWeapon_Component : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeapon_Component();

	virtual void Start_Fire();

	void Stop_Fire();

	void Reload();

	bool Is_Fire() const;

	bool Get_Current_Ammo(FAmmo& CurrentAmmo) const;

	bool To_Add_Ammo(TSubclassOf<ABase_Weapon> WeaponType, int32 ClipsAmount);

	bool Need_Ammo(TSubclassOf<ABase_Weapon> WeaponType);

	ABase_Weapon* Get_Current_Weapon();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABase_Weapon> Weapon_Class;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName Weapon_Socket_Name = "Weapon_Socket";

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float Reload_Duration = 1.0f;

	FTimerHandle Reload_Timer_Handle;

	UPROPERTY()
	ABase_Weapon* Current_Weapon = nullptr;

	bool Reloading = false;

private:
	void Spawn_Weapon();
	void Attach_Weapon_To_Socket(ABase_Weapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	bool Can_Reload() const;

	UFUNCTION()
	void On_Empty_Clip();

	void Change_Clip();
};
