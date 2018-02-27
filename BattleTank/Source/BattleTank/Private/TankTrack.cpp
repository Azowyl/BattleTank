// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle) {
	auto ForceToApply = GetForwardVector() * throttle * MaxThrottleForce;
	auto ForceLocation = GetComponentLocation();
	auto RootTank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	RootTank->AddForceAtLocation(ForceToApply, ForceLocation);
}
