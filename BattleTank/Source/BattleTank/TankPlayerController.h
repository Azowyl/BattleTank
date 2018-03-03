// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank * GetControlledTank() const;
	
	void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = .5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = .33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000; // 10 km.

	/* Methods */

	void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	// return true if hits landscape
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;

	bool GetLookDirection(FVector2D &ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
