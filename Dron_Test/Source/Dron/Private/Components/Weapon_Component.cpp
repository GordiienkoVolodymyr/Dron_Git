#include "Components/Weapon_Component.h"
#include "Player/Base_Pawn.h"

UWeapon_Component::UWeapon_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UWeapon_Component::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Current_Weapon)
	{
		Current_Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Current_Weapon->Destroy();
	}
	Super::EndPlay(EndPlayReason);
}

void UWeapon_Component::Spawn_Weapon()
{
	auto Pawn = Cast<ABase_Pawn>(GetOwner());
	if (!Pawn || !GetWorld())
	{
		return;
	}

	auto Weapon = GetWorld()->SpawnActor<ABase_Weapon>(Weapon_Class);
	if (!Weapon) return;

	Weapon->On_Clip_Empty.AddUObject(this, &UWeapon_Component::On_Empty_Clip);
	Weapon->SetOwner(Pawn);
	Current_Weapon = Weapon;
	Attach_Weapon_To_Socket(Weapon, Pawn->Get_Mesh(), Weapon_Socket_Name);
}

void UWeapon_Component::Attach_Weapon_To_Socket(ABase_Weapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;

	const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	Weapon->AttachToComponent(SceneComponent, AttachmentTransformRules, SocketName);

}

bool UWeapon_Component::Can_Reload() const
{
	return !Reloading && Current_Weapon->Can_Reload();
}

void UWeapon_Component::On_Empty_Clip()
{
	if (Current_Weapon)
	{
		Reloading = true;
		GetOwner()->GetWorldTimerManager().SetTimer(Reload_Timer_Handle, FTimerDelegate::CreateLambda([this]()
			{
				this->Reloading = false;
				Change_Clip();
			}), Reload_Duration, false);
	}
}

void UWeapon_Component::Change_Clip()
{
	if (!Can_Reload()) return;

	Current_Weapon->Stop_Fire();
	Current_Weapon->Changed_Clip();
}

void UWeapon_Component::Start_Fire()
{
	if (!Current_Weapon)
	{
		return;
	}
	Current_Weapon->Start_Fire();
}

void UWeapon_Component::Stop_Fire()
{
	if (!Current_Weapon)
	{
		return;
	}
	Current_Weapon->Stop_Fire();
}

void UWeapon_Component::Reload()
{
	Change_Clip();
}

bool UWeapon_Component::Is_Fire() const
{
	return Current_Weapon && Current_Weapon->Shooting_In_Action();
}

bool UWeapon_Component::Get_Current_Ammo(FAmmo& CurrentAmmo) const
{
	if (Current_Weapon)
	{
		CurrentAmmo = Current_Weapon->Get_Current_Ammo();
		return true;
	}
	return false;
}

bool UWeapon_Component::To_Add_Ammo(TSubclassOf<ABase_Weapon> WeaponType, int32 ClipsAmount)
{
	if (Current_Weapon)
	{
		return Current_Weapon->Add_Ammo(ClipsAmount);
	}
	return false;
}

bool UWeapon_Component::Need_Ammo(TSubclassOf<ABase_Weapon> WeaponType)
{
	if (Current_Weapon)
	{
		return !Current_Weapon->Is_Ammo_Full();
	}
	return false;
}

ABase_Weapon* UWeapon_Component::Get_Current_Weapon()
{
	return Current_Weapon;
}

void UWeapon_Component::BeginPlay()
{
	Super::BeginPlay();

	Spawn_Weapon();
}
