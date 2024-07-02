// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Missile_Projectile.generated.h"

UCLASS()
class DRON_API AMissile_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AMissile_Projectile();

	void Set_Shot_Direction(const FVector& Direction);
	void Set_Damage_Amount(const float Damage);
	void Set_Damage_Radius(const float Radius);
	void Set_Full_Damage(const bool full_damage);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void On_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UBoxComponent* Box_Component;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* Movement_Component;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Life_Time = 5.0f;
private:

	FVector Shot_Direction;
	float Damage_Amount;
	float Damage_Radius;
	bool Full_Damage;

	AController* Get_Controller() const;

};
