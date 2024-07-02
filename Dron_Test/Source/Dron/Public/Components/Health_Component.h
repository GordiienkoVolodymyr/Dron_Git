#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health_Component.generated.h"

DECLARE_MULTICAST_DELEGATE(FOn_Death_Signature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOn_Health_Changed_Signature, float, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRON_API UHealth_Component : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealth_Component();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool Is_Health_Max();

	bool Add_health(float Health_Amount);

	void Set_Health(float Health_Amount);

	float Get_Health() const;

	UFUNCTION(BlueprintCallable)
	bool Is_Dead() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float Get_Health_Percent() const;

	FOn_Health_Changed_Signature On_Health_Changed;
	FOn_Death_Signature On_Death;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float Max_Health;

private:

	UFUNCTION()
	void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

	void Apply_Damage(float Damage, AController* InstigatedBy);

	float Health;
		
};
