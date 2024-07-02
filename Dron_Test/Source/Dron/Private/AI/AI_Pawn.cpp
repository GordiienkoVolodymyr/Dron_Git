#include "AI/AI_Pawn.h"

AAI_Pawn::AAI_Pawn()
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ATurret_Enemy_AIController::StaticClass();

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidget");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

ATurret_Enemy_AIController* AAI_Pawn::Get_AI_Controller() const
{
    return AI_Controller;
}

void AAI_Pawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    Update_Health_Widget_Visibility();
}

void AAI_Pawn::Set_AI_Controller()
{
    AI_Controller = Cast<ATurret_Enemy_AIController>(GetController());
}

void AAI_Pawn::BeginPlay()
{
    Super::BeginPlay();

    Set_AI_Controller();

    check(HealthWidgetComponent);
}

void AAI_Pawn::On_Death()
{
    Super::On_Death();

    if (AI_Controller && AI_Controller->BrainComponent)
    {
        AI_Controller->BrainComponent->Cleanup();
    }
}

void AAI_Pawn::On_Health_Changed(float Health, float HealthDelta)
{
    Super::On_Health_Changed(Health, HealthDelta);

    const auto Health_Bar_Widget = Cast<UHealth_UserWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!Health_Bar_Widget)
    {
        return;
    }
    Health_Bar_Widget->Set_Health_Percent(Health_Component->Get_Health_Percent());
}

void AAI_Pawn::Update_Health_Widget_Visibility()
{
    if (!GetWorld() ||                             //
        !GetWorld()->GetFirstPlayerController() || //
        !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
        return;

    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}