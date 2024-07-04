// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class THELONECAPTAIN_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void AsyncPhysicsTickActor(float DeltaTime, float SimTime) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UCapsuleComponent* playerCapsule;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* playerMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UCameraComponent* playerCamera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float lookSensitivity = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float walkSpeed = 1500.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float sprintSpeed = 1800.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float friction = 0.82f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float acceleration = 10000.0f;

private:
	static FString VectorToString(const FVector& vector);
	
	UPROPERTY(EditAnywhere, Category="Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_MAX;
	
	void PlayerMovement(const float& deltaTime);
	void PlayerLook();
	void PlayerVelocity(const float& deltaTime);
	void PlayerGrounded();

	FVector playerEulerAngles;
	FVector playerEulerAnglesTarget;
	FVector velocity;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true)) FVector2f movementInput;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true)) FVector2f mouseDelta;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true)) bool sprinting;
};
