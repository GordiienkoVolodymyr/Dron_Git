// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Player_Weapon.h"

APlayer_Weapon::APlayer_Weapon()
{
    Missile_Spawn = FVector(0.0f, 0.0f, 0.0f);
    Damage_Amount = 25.0f;
    Full_Damege = false;
}

void APlayer_Weapon::Make_Shot()
{
    if (!GetWorld()) return;

    if (Is_Ammo_Empty())
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), nullptr, GetActorLocation());
        return;
    }

    FVector Trace_Start, Trace_End;
    if (!Get_Trace_Data(Trace_Start, Trace_End)) return;

    FHitResult Hit_Result;
    Make_Hit(Hit_Result, Trace_Start, Trace_End);

    const FVector End_Point = Hit_Result.bBlockingHit ? Hit_Result.ImpactPoint : Trace_End;
    const FVector Direction = (End_Point - Get_Muzzle_World_Location()).GetSafeNormal();

    const FVector SpawnLocation = Get_Muzzle_World_Location() + Missile_Spawn;
    FTransform SpawnTransform(Direction.Rotation(), SpawnLocation);

    AMissile_Projectile* Projectile = GetWorld()->SpawnActorDeferred<AMissile_Projectile>(Missile, SpawnTransform);
    if (Projectile)
    {
        Projectile->Set_Shot_Direction(Direction);
        Projectile->Set_Damage_Amount(Damage_Amount);
        Projectile->Set_Damage_Radius(Damage_Radius);
        Projectile->Set_Full_Damage(Full_Damege);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    Decrease_Ammo();

    //UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);

}

void APlayer_Weapon::Start_Fire()
{
    Super::Start_Fire();
    Make_Shot();
}
