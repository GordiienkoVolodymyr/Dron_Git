#include "Player/Base_Pawn.h"

ABase_Pawn::ABase_Pawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Box_Colision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_Component"));
	Skeletal_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal_Mesh"));
	Health_Component = CreateDefaultSubobject<UHealth_Component>(TEXT("Health_Component"));
	Weapon_Component = CreateDefaultSubobject<UWeapon_Component>(TEXT("Weapon_Component"));

	RootComponent = Box_Colision;
	Skeletal_Mesh->SetupAttachment(Box_Colision);
}

void ABase_Pawn::BeginPlay()
{
	Super::BeginPlay();

	On_Health_Changed(Health_Component->Get_Health(), 0.0f);
	Health_Component->On_Death.AddUObject(this, &ABase_Pawn::On_Death);
	Health_Component->On_Health_Changed.AddUObject(this, &ABase_Pawn::On_Health_Changed);
}

void ABase_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABase_Pawn::On_Health_Changed(float Health, float HealthDelta)
{

}

void ABase_Pawn::On_Death()
{
	Destroy();
}

USkeletalMeshComponent* ABase_Pawn::Get_Mesh() const
{
	return Skeletal_Mesh;
}