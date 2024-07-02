#include "Player/Dron_Pawn.h"

DEFINE_LOG_CATEGORY_STATIC(DamageLog, All, All);

ADron_Pawn::ADron_Pawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Movement_Component = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement_Component"));
	Camera_Component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera_Component"));

	Camera_Component->SetupAttachment(RootComponent);
	Movement_Component->SetUpdatedComponent(RootComponent);

	Movement_Component->MaxSpeed = 800.0f;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
}

void ADron_Pawn::BeginPlay()
{
	Super::BeginPlay();
}

void ADron_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADron_Pawn::Move_Forward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADron_Pawn::Move_Right);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADron_Pawn::Move_Up);
	PlayerInputComponent->BindAxis("MoveDown", this, &ADron_Pawn::Move_Down);
	PlayerInputComponent->BindAxis("LookUp", this, &ADron_Pawn::Look_Up);
	PlayerInputComponent->BindAxis("LookRight", this, &ADron_Pawn::Look_Right);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, Weapon_Component, &UWeapon_Component::Start_Fire);
}

void ADron_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADron_Pawn::Move_Forward(float Axsis)
{
	AddMovementInput(GetActorForwardVector(), Axsis);
}

void ADron_Pawn::Move_Right(float Axsis)
{
	AddMovementInput(GetActorRightVector(), Axsis);
}

void ADron_Pawn::Look_Up(float Axsis)
{
	AddControllerPitchInput(-Axsis);
}

void ADron_Pawn::Look_Right(float Axsis)
{
	AddControllerYawInput(Axsis);
}

void ADron_Pawn::Move_Up(float Axsis)
{
	AddMovementInput(GetActorUpVector(), Axsis);
}

void ADron_Pawn::Move_Down(float Axsis)
{
	AddMovementInput(GetActorUpVector(), Axsis);
}
