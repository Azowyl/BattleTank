// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAimingComponent.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTankDeath();

	UPROPERTY(EditDefaultsonly, Category = Setup)
	float AcceptanceRadius = 7000;

	UTankAimingComponent* AimingComponent = nullptr;
};
