#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Logging/LogMacros.h"
#include "Health_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API UHealth_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void Set_Health_Percent(float Percent);

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* Health_Progress_Bar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float Percent_Visibility_Threshold = 0.8f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float Percent_Color_Threshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor Good_Color = FLinearColor::Green;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor Bad_Color = FLinearColor::Red;
};
