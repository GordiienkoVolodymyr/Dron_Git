// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Core.h"
#include "Base_Weapon.generated.h"
DECLARE_MULTICAST_DELEGATE(FOn_Clip_Empty_Signature);

USTRUCT(BlueprintType)
struct FAmmo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon");
	int64 Missile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int64 Clips;
};

UCLASS()
class DRON_API ABase_Weapon : public AActor
{
	GENERATED_BODY()
	
public:
	ABase_Weapon();

	virtual void Tick(float DeltaTime) override;

	virtual void Start_Fire();

	virtual void Stop_Fire();

	bool Shooting_In_Action() const;

	void Changed_Clip();

	bool Can_Reload() const;

	FAmmo Get_Current_Ammo() const { return Current_Ammo; }

	bool Add_Ammo(int64 Clip_Amount);

	bool Is_Ammo_Empty() const;

	bool Is_Ammo_Full() const;

	FOn_Clip_Empty_Signature On_Clip_Empty;

protected:
	virtual void BeginPlay() override;

	virtual void Make_Shot();

	bool Get_Player_View_Point(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector Get_Muzzle_World_Location() const;

	virtual bool Get_Trace_Data(FVector& TraceStart, FVector& TraceEnd) const;

	void Make_Hit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void Decrease_Ammo();

	bool Is_Clip_Empty() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* Weapon_Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Damage_Amount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	FName Muzzle_Socket_Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Trace_Max_Distance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmo Default_Ammo{ 1, 3 };

private:
	bool Is_Fire = false;

	FAmmo Current_Ammo;

};
