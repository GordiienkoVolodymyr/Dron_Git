#include "Components/Health_Component.h"

UHealth_Component::UHealth_Component()
{
	PrimaryComponentTick.bCanEverTick = false;

	Max_Health = 100.0f;
}

void UHealth_Component::BeginPlay()
{
	Super::BeginPlay();

	Set_Health(Max_Health);

	if (AActor* Component_Owner = GetOwner())
	{
		Component_Owner->OnTakeRadialDamage.AddDynamic(this, &UHealth_Component::OnTakeRadialDamage);
	}
}

void UHealth_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UHealth_Component::Is_Health_Max()
{
	return FMath::IsNearlyEqual(Health, Max_Health);
}

bool UHealth_Component::Add_health(float Health_Amount)
{
	if (Is_Health_Max())
	{
		return false;
	}
	Set_Health(Health_Amount + Health);
	return true;
}

void UHealth_Component::Set_Health(float Health_Amount)
{
	const auto Temp_Health = FMath::Clamp(Health_Amount, 0.0f, Max_Health);
	const auto Heath_Delta = Health_Amount - Health;
	Health = Temp_Health;
	On_Health_Changed.Broadcast(Health, Heath_Delta);
}

bool UHealth_Component::Is_Dead() const
{
	return Health <= 0.0f;
}

float UHealth_Component::Get_Health_Percent() const
{
	return Health / Max_Health;
}

void UHealth_Component::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	Apply_Damage(Damage, InstigatedBy);
}

void UHealth_Component::Apply_Damage(float Damage, AController* InstigatedBy)
{
	if (Damage == 0.0f || Is_Dead(), !GetWorld())
	{
		return;
	}

	Set_Health(Health - Damage);

	if (Is_Dead())
	{
		On_Death.Broadcast();
	}
}

float UHealth_Component::Get_Health() const
{
	return Health;
}
