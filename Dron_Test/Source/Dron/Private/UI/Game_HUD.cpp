#include "UI/Game_HUD.h"

void AGame_HUD::BeginPlay()
{
    Super::BeginPlay();

    Player_Hud_Widget = CreateWidget<UUserWidget>(GetWorld(), Player_Hud_Widget_Class);

    if (Player_Hud_Widget)
    {
        Player_Hud_Widget->AddToViewport();
    }
}
