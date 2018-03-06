// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.generated.h"

#define OUT

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* AimingComponent = nullptr;

private:
	UPROPERTY(EditDefaultsonly)
	float CrossHairXLocation = .5f;

	UPROPERTY(EditDefaultsonly)
	float CrossHairYLocation = .33333f;

	UPROPERTY(EditDefaultsonly)
	float LineTraceRange = 1000000; // 10 km.

	/* Methods */

	void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	// return true if hits landscape
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;

	bool GetLookDirection(FVector2D &ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
