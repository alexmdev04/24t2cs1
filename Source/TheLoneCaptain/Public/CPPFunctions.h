// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPFunctions.generated.h"

/**
 * 
 */
UCLASS()
class THELONECAPTAIN_API UCPPFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayerMovement"), Category = "Player Controller")
		static void PlayerMovement(const float& fixedDeltaTime, APawn* playerPawn, float inputX, float inputY, float playerWalkSpeed, float
		                           playerSprintSpeed, float
		                           friction, bool sprinting);
	private:
		static void SetPlayerVelocity(APawn* playerPawn, FVector velocity, const float& fixedDeltaTime);
		static FString VectorToString(const FVector& vector);
};
