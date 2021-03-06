// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure)
	float GetCurrentHealthAsPercentage() const;

	FTankDelegate OnDeath;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float StartingHealth = 100;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
