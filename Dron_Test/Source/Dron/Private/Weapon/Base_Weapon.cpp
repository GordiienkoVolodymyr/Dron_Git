// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Base_Weapon.h"

ABase_Weapon::ABase_Weapon()
{
	Weapon_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon_Mesh"));
	SetRootComponent(Weapon_Mesh);

	Muzzle_Socket_Name = "Weapon_Socket";
}

void ABase_Weapon::BeginPlay()
{
	Super::BeginPlay();

	Current_Ammo = Default_Ammo;
}

void ABase_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABase_Weapon::Make_Shot()
{
}

bool ABase_Weapon::Get_Player_View_Point(FVector& ViewLocation, FRotator& ViewRotation) const
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn)
	{
		return false;
	}

	if (Pawn->IsPlayerControlled())
	{
		APlayerController* Controller = Pawn->GetController<APlayerController>();
		if (!Controller)
		{
			return false;
		}

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = Get_Muzzle_World_Location();
		ViewRotation = Weapon_Mesh->GetSocketRotation(Muzzle_Socket_Name);
	}
	return true;
}

FVector ABase_Weapon::Get_Muzzle_World_Location() const
{
	return Weapon_Mesh->GetSocketLocation(Muzzle_Socket_Name);
}

bool ABase_Weapon::Get_Trace_Data(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if (!Get_Player_View_Point(ViewLocation, ViewRotation))
	{
		return false;
	}

	TraceStart = ViewLocation;
	const FVector Shoot_Direction = ViewRotation.Vector();

	TraceEnd = TraceStart + Shoot_Direction * Trace_Max_Distance;
	return true;
}

void ABase_Weapon::Make_Hit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld())
	{
		return;
	}

	FCollisionQueryParams Collision_Params;
	Collision_Params.AddIgnoredActor(GetOwner());
	Collision_Params.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, Collision_Params);

}

void ABase_Weapon::Decrease_Ammo()
{
	if (Current_Ammo.Missile == 0)
	{
		return;
	}
	Current_Ammo.Missile--;

	if (Is_Clip_Empty() && !Is_Ammo_Empty())
	{
		Stop_Fire();
		On_Clip_Empty.Broadcast();
	}
}

void ABase_Weapon::Start_Fire()
{
	Is_Fire = true;
}

void ABase_Weapon::Stop_Fire()
{
	Is_Fire = false;
}

bool ABase_Weapon::Shooting_In_Action() const
{
	return Is_Fire;
}

void ABase_Weapon::Changed_Clip()
{
	Current_Ammo.Missile = Default_Ammo.Missile;

	if (Current_Ammo.Clips == 0)
	{
		return;
	}
	Current_Ammo.Clips--;
}

bool ABase_Weapon::Can_Reload() const
{
	return Current_Ammo.Missile < Default_Ammo.Missile && Current_Ammo.Clips > 0;;
}

bool ABase_Weapon::Add_Ammo(int64 Clip_Amount)
{
	if (Is_Ammo_Full() || Clip_Amount <= 0)
	{
		return false;
	}

	if (Is_Ammo_Empty())
	{

		Current_Ammo.Clips = FMath::Clamp(Clip_Amount, 0, Default_Ammo.Clips + 1);
		On_Clip_Empty.Broadcast();
	}
	else if (Current_Ammo.Clips < Default_Ammo.Clips)
	{
		const auto NextClipsAmount = Current_Ammo.Clips + Clip_Amount;
		if (Default_Ammo.Clips - NextClipsAmount >= 0)
		{
			Current_Ammo.Clips = NextClipsAmount;
		}
		else
		{
			Current_Ammo.Clips = Default_Ammo.Clips;
			Current_Ammo.Missile = Default_Ammo.Missile;
		}
	}
	else
	{
		Current_Ammo.Missile = Default_Ammo.Missile;
	}
	return true;
}

bool ABase_Weapon::Is_Ammo_Empty() const
{
	return Current_Ammo.Clips == 0 && Is_Clip_Empty();;
}

bool ABase_Weapon::Is_Ammo_Full() const
{
	return Current_Ammo.Clips == Default_Ammo.Clips && Current_Ammo.Missile == Default_Ammo.Missile;
}

bool ABase_Weapon::Is_Clip_Empty() const
{
	return Current_Ammo.Missile == 0;
}
