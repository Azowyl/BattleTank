// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle) {
	auto ForceToApply = GetForwardVector() * throttle * MaxThrottleForce;
	auto ForceLocation = GetComponentLocation();
	auto RootTank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	RootTank->AddForceAtLocation(ForceToApply, ForceLocation);
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	auto SlippageSpeed = FVector::DotProduct(FVector::RightVector, GetComponentVelocity());
	auto CorrectionAcceleration = -SlippageSpeed * FVector::RightVector / DeltaTime;

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // 2 tracks

	this->AddForceAtLocation(CorrectionForce, GetComponentLocation());
}
