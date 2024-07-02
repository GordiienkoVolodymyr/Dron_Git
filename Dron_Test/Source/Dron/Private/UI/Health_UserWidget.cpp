// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Health_UserWidget.h"

void UHealth_UserWidget::Set_Health_Percent(float Percent)
{
	if (!Health_Progress_Bar)
	{
		return;
	}

	const ESlateVisibility Health_Bar_Visibility = (Percent > Percent_Visibility_Threshold
		|| FMath::IsNearlyZero(Percent))
		? ESlateVisibility::Hidden
		: ESlateVisibility::Visible;
	Health_Progress_Bar->SetVisibility(Health_Bar_Visibility);

	const auto Health_Bar_Color = Percent > Percent_Color_Threshold ? Good_Color : Bad_Color;
	Health_Progress_Bar->SetFillColorAndOpacity(Health_Bar_Color);

	Health_Progress_Bar->SetPercent(Percent);
}
