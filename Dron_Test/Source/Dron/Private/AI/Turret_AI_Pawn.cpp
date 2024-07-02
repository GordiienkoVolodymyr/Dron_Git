// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Turret_AI_Pawn.h"

ATurret_AI_Pawn::ATurret_AI_Pawn()
{
	Stand_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scene_Component"));
	Stand_Mesh->SetupAttachment(RootComponent);

	Min_Pitch = -30.0f;
	Max_Pitch = 30.0f;
}

void ATurret_AI_Pawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (AI_Controller && AI_Controller->GetFocusActor())
	{
		Rotate_Towards_Focus_Actor(AI_Controller->GetFocusActor());
	}
}

void ATurret_AI_Pawn::Rotate_Towards_Focus_Actor(const AActor* FocusActor)
{
    if (!FocusActor)
    {
        return;
    }

    const FVector Direction_To_Focus = FocusActor->GetActorLocation() - GetActorLocation();
    const FRotator Rotation_To_Focus = UKismetMathLibrary::MakeRotFromX(Direction_To_Focus);

    FRotator Clamped_Rotation = FRotator(FMath::Clamp(Rotation_To_Focus.Pitch, Min_Pitch, Max_Pitch), Rotation_To_Focus.Yaw,
        Rotation_To_Focus.Roll);

    if (!Weapon_Component && !Weapon_Component->Get_Current_Weapon())
    {
        return;
    }

    Weapon_Component->Get_Current_Weapon()->SetActorRotation(Clamped_Rotation);

    const FRotator Leg_Rotation_To_Focus_Actor = FRotator(0.0f, Clamped_Rotation.Yaw, Clamped_Rotation.Roll);
    Scene_Component->SetWorldRotation(Leg_Rotation_To_Focus_Actor);
}
