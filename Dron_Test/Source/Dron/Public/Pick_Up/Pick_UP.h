#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Pick_UP.generated.h"

UCLASS()
class DRON_API APick_UP : public AActor
{
	GENERATED_BODY()
	
public:
    APick_UP();

    virtual void Tick(float DeltaTime) override;

    bool Could_Be_Taken() const;

protected:
    virtual void BeginPlay() override;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Collision_Component;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    bool Can_Respawn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float Respawn_Time;

    /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundCue* PickupSound;*/

    UPROPERTY()
    TArray<APawn*> Overlapping_Pawns;

private:
    float Rotation_Yaw;
    FTimerHandle Respawn_Timer;

    virtual bool Give_Pickup_To(APawn* Pawn);
    void Pickup_Was_Taken();
    void Respawn();
    void Generate_Rotation_Yaw();

};
