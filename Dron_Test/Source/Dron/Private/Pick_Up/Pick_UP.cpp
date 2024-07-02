#include "Pick_Up/Pick_UP.h"
APick_UP::APick_UP()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Collision_Component = CreateDefaultSubobject<USphereComponent>(TEXT("Collision_Component"));

	Collision_Component->InitSphereRadius(50.0f);
	Collision_Component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision_Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(Collision_Component);

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(RootComponent);

	Respawn_Time = 5.0f;
	Can_Respawn = true;
	Rotation_Yaw = 0.0f;
}

void APick_UP::BeginPlay()
{
	Super::BeginPlay();

	Generate_Rotation_Yaw();
}

void APick_UP::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (Give_Pickup_To(Pawn))
	{
		Pickup_Was_Taken();
	}
	else if (Pawn)
	{
		Overlapping_Pawns.Add(Pawn);
	}
}

void APick_UP::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	APawn* Pawn = Cast<APawn>(OtherActor);
	Overlapping_Pawns.Remove(Pawn);
}

void APick_UP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, Rotation_Yaw, 0.0f));

	for (APawn* Overlap_Pawn : Overlapping_Pawns)
	{
		if (Give_Pickup_To(Overlap_Pawn))
		{
			Pickup_Was_Taken();
			break;
		}
	}
}

bool APick_UP::Could_Be_Taken() const
{
	return GetWorldTimerManager().IsTimerActive(Respawn_Timer);
}

bool APick_UP::Give_Pickup_To(APawn* Pawn)
{
	return false;
}

void APick_UP::Pickup_Was_Taken()
{
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}
	Collision_Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), nullptr, GetActorLocation());

	if (!Can_Respawn) return;
	GetWorldTimerManager().SetTimer(Respawn_Timer, this, &APick_UP::Respawn, Respawn_Time);

}

void APick_UP::Respawn()
{
	Generate_Rotation_Yaw();

	Collision_Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}

void APick_UP::Generate_Rotation_Yaw()
{
	float Direction = FMath::RandBool() ? 1.0f : -1.0f;
	Rotation_Yaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}


