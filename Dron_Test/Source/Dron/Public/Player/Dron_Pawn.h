// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Player/Base_Pawn.h"
#include "Dron_Pawn.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API ADron_Pawn : public ABase_Pawn
{
	GENERATED_BODY()
public:
	ADron_Pawn();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UFloatingPawnMovement* Movement_Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera_Component;

private:

	void Move_Forward(float Axsis);
	void Move_Right(float Axsis);
	void Look_Up(float Axsis);
	void Look_Right(float Axsis);
	void Move_Up(float Axsis);
	void Move_Down(float Axsis);
};
