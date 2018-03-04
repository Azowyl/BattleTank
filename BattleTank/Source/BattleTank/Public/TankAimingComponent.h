// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Aiming,
	Reloading,
	Locked,
};

class UTankBarrel;
class UTankTorret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* Barrel, UTankTorret* Torret);

	void AimAt(FVector HitLocation);

	void MoveBarrelTowards(FVector AimDirection);

	EFiringStatus GetFiringStatus() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

private:
	UTankBarrel * Barrel = nullptr;
	UTankTorret * Torret = nullptr;

	UPROPERTY(EditDefaultsonly)
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ReloadTime = 3;

	float LastTimeShot;

	FVector LastBarrelPosition;

	bool IsBarrelMoving() const;
};
