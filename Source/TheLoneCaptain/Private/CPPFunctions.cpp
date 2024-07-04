// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPFunctions.h"
#include "Kismet/KismetMathLibrary.h"

void UCPPFunctions::PlayerMovement(const float& fixedDeltaTime, APawn* playerPawn,  float inputX, float inputY, float playerWalkSpeed, float playerSprintSpeed, float friction, bool sprinting)
{
	const FVector playerForward = playerPawn->GetActorForwardVector();

	constexpr float acceleration = 100.0f;
	const float maxVelocity = sprinting ? playerWalkSpeed : playerSprintSpeed;
	const FVector movementDirection = FVector(inputX, inputY, 0.0f) * playerForward;

	if (playerPawn->GetVelocity().Z == 0.0L)
	{
		// apply friction
		float speed = playerPawn->GetVelocity().Size();
		if (speed <= 0.1f) { SetPlayerVelocity(playerPawn, FVector(0.0f,0.0f,0.0f), fixedDeltaTime); }
		SetPlayerVelocity(playerPawn, playerPawn->GetVelocity() * friction, fixedDeltaTime);
	}
	double projVel = UKismetMathLibrary::Dot_VectorVector(playerPawn->GetVelocity(), movementDirection); // Vector projection of Current velocity onto accelDir.
	double accelVel = acceleration * fixedDeltaTime; // Accelerated velocity in direction of movment

	// If necessary, truncate the accelerated velocity so the vector projection does not exceed max_velocity
	if (projVel + accelVel > maxVelocity) { accelVel = maxVelocity - projVel; }
	SetPlayerVelocity(playerPawn, playerPawn->GetVelocity() + (movementDirection * accelVel), fixedDeltaTime);
	
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, VectorToString(playerPawn->GetVelocity()));
}

void UCPPFunctions::SetPlayerVelocity(APawn* playerPawn, FVector velocity, const float& fixedDeltaTime)
{
	velocity = FVector(velocity.X, velocity.Y, 0.0f);
	const FVector& location = playerPawn->GetActorLocation();
	const FVector& newLocation = UKismetMathLibrary::VLerp(location, location + velocity, fixedDeltaTime * 1000.0f);
	playerPawn->SetActorLocation(newLocation);
}

FString UCPPFunctions::VectorToString(const FVector& vector)
{
	return FString("(") + FString::SanitizeFloat(vector.X) + ", " + FString::SanitizeFloat(vector.Y) + ", " + FString::SanitizeFloat(vector.Z) + ")";
}
