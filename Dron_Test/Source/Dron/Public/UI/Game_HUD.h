#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Game_HUD.generated.h"


UCLASS()
class DRON_API AGame_HUD : public AHUD
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> Player_Hud_Widget_Class;

    UUserWidget* Player_Hud_Widget;
};
