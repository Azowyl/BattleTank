// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTorret.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	
	LastTimeShot = GetWorld()->GetTimeSeconds();
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }

	return !Barrel->GetForwardVector().Equals(LastBarrelPosition, 0.01);
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((GetWorld()->GetTimeSeconds() - LastTimeShot) < ReloadTime)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving() && CurrentAmmo > 0)
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else if (CurrentAmmo > 0)
	{
		FiringStatus = EFiringStatus::Locked;
	}
	else
	{
		FiringStatus = EFiringStatus::Out;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * Barrel, UTankTorret * Torret)
{
	if (!ensure(Barrel) || !ensure(Torret)) { return; }

	this->Barrel = Barrel;
	this->Torret = Torret;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, 
		OutLaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed, 
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		LastBarrelPosition = AimDirection;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);

	auto TurretRotator = Torret->GetForwardVector().Rotation();
	auto TurretDeltaRotator = AimAsRotator - TurretRotator;

	if (FMath::Abs(TurretDeltaRotator.Yaw) > 180.0)
	{
		TurretDeltaRotator = -1 * TurretDeltaRotator;
	}

	Torret->Rotate(TurretDeltaRotator.Yaw);
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

void UTankAimingComponent::Fire()
{
	bool IsReloaded = FiringStatus != EFiringStatus::Reloading;

	if (Barrel && IsReloaded && CurrentAmmo > 0) {
		auto Location = Barrel->GetSocketLocation(FName("Projectile"));
		auto Rotation = Barrel->GetSocketRotation(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		LastTimeShot = GetWorld()->GetTimeSeconds();
		CurrentAmmo--;
	}
}
