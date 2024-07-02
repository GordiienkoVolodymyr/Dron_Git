#include "Weapon/Missile_Projectile.h"

AMissile_Projectile::AMissile_Projectile()
{
	Box_Component = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_Component"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Movement_Component = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement_Component"));

	Box_Component->SetBoxExtent(FVector(35.0f, 6.0f, 6.0f));
	Box_Component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box_Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Box_Component->bReturnMaterialOnMove = true;
	SetRootComponent(Box_Component);

	Mesh->SetupAttachment(RootComponent);

	Movement_Component->InitialSpeed = 2000.0f;
	Movement_Component->ProjectileGravityScale = 0.0f;
}

void AMissile_Projectile::BeginPlay()
{
	Super::BeginPlay();

	Movement_Component->Velocity = Shot_Direction * Movement_Component->InitialSpeed;
	Box_Component->OnComponentHit.AddDynamic(this, &AMissile_Projectile::On_Hit);
	Box_Component->IgnoreActorWhenMoving(GetOwner(), true);
	SetLifeSpan(Life_Time);
}

void AMissile_Projectile::On_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	Movement_Component->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage_Amount, GetActorLocation(), Damage_Radius, UDamageType::StaticClass(), {}, this, Get_Controller(), Full_Damage);

	//WeaponFXComponent->PlayImpactEffects(Hit);
	Destroy();
}

AController* AMissile_Projectile::Get_Controller() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}


void AMissile_Projectile::Set_Shot_Direction(const FVector& Direction)
{
	Shot_Direction = Direction;
}

void AMissile_Projectile::Set_Damage_Amount(const float Damage)
{
	Damage_Amount = Damage;
}

void AMissile_Projectile::Set_Damage_Radius(const float Radius)
{
	Damage_Radius = Radius;
}

void AMissile_Projectile::Set_Full_Damage(const bool full_damage)
{
	Full_Damage = full_damage;
}
