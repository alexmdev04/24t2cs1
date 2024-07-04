#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	bAsyncPhysicsTickEnabled = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	playerCapsule = CreateDefaultSubobject<UCapsuleComponent>(FName("playerCollider"));
	playerCapsule->SetCapsuleHalfHeight(96.0f);
	playerCapsule->SetCapsuleRadius(45.0f);
	playerCapsule->SetCollisionProfileName(TEXT("Pawn"));
	playerCapsule->SetSimulatePhysics(true);
	playerCapsule->GetBodyInstance()->bLockXRotation = true;
	playerCapsule->GetBodyInstance()->bLockYRotation = true;
	SetRootComponent(playerCapsule);
	
	playerMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("playerMesh"));
	playerMesh->SetupAttachment(playerCapsule);
	playerMesh->SetWorldScale3D(UE::Math::TVector<double>(1.8f, 1.8f, 1.92f));
	playerMesh->SetRelativeLocation(UE::Math::TVector<double>(0.0f,0.0f,-96.0f));
	playerMesh->SetCollisionProfileName(TEXT("NoCollision"));
	playerMesh->SetGenerateOverlapEvents(false);
	
	playerCamera = CreateDefaultSubobject<UCameraComponent>(FName("playerCamera"));
	playerCamera->SetupAttachment(playerCapsule);
	playerCamera->SetRelativeLocation(UE::Math::TVector<double>(-10.0f,0.0f,60.0f));
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerMovement(DeltaTime);
	PlayerVelocity(DeltaTime);
	PlayerLook();
}

void APlayerPawn::AsyncPhysicsTickActor(float DeltaTime, float SimTime)
{
	Super::AsyncPhysicsTickActor(DeltaTime, SimTime);
	PlayerGrounded();
}

void APlayerPawn::PlayerMovement(const float& deltaTime)
{	
	const float maxVelocity = sprinting ? walkSpeed : sprintSpeed;
	const FVector movementDirection = UKismetMathLibrary::TransformDirection(
		GetTransform(), FVector(movementInput.Y, movementInput.X, 0.0f));
	
	if (velocity.Z == 0.0L)
	{
		// apply friction
		float speed = velocity.Size();
		if (speed <= 0.1f) { velocity = FVector(0.0f,0.0f,0.0f); }
		velocity *= friction;
	}
	float projVel = UKismetMathLibrary::Dot_VectorVector(velocity, movementDirection); // Vector projection of Current velocity onto accelDir.
	float accelVel = acceleration * deltaTime; // Accelerated velocity in direction of movment

	// If necessary, truncate the accelerated velocity so the vector projection does not exceed max_velocity
	if (projVel + accelVel > maxVelocity) { accelVel = maxVelocity - projVel; }
	velocity += movementDirection * accelVel;
	
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, VectorToString(velocity));
}

void APlayerPawn::PlayerVelocity(const float& deltaTime)
{
	const FVector& location = this->GetActorLocation();
	const FVector& newLocation = UKismetMathLibrary::VLerp(location, location + velocity, deltaTime);
	this->SetActorLocation(newLocation);

	// float gameTime = 0.0f;
	// gameTime += deltaTime;
	//
	// acceleration = force(gameTime, location) / mass;
	// position += deltaTime * (velocity + deltaTime * acceleration / 2);
	// newAcceleration = force(gameTime, location) / mass;
	// velocity += deltaTime * (acceleration + newAcceleration) / 2;
	//
	// location += deltaTime * (velocity + deltaTime * acceleration / 2);
	// velocity += deltaTime * acceleration;
}

void APlayerPawn::PlayerGrounded()
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + (-GetActorUpVector() * 1000.0f);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	GetWorld()->LineTraceSingleByProfile(Hit, TraceStart, TraceEnd, FName("PhysicsActor"), QueryParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 0.25f, 0, 1.0f);
	
	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (!Hit.bBlockingHit && !IsValid(Hit.GetActor())) return;
	if (Hit.GetActor()->Tags.IsEmpty()) return;
	if (Hit.GetActor()->Tags[0] != FName("ship")) return;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "on ship");
	//bool onShip = true;
}

void APlayerPawn::PlayerLook()
{
	playerEulerAngles += FVector(0.0f, -mouseDelta.Y * lookSensitivity, mouseDelta.X * lookSensitivity);
	playerEulerAngles.Y = UKismetMathLibrary::ClampAngle(playerEulerAngles.Y, -90.0L, 90.0L),
	playerCapsule->SetRelativeRotation(FRotator(0.0f, playerEulerAngles.Z, 0.0f));
	playerCamera->SetRelativeRotation(FRotator(playerEulerAngles.Y, 0.0f, 0.0f));
	
	// vectorUp = FVector(0.0f,0.0f,1.0f);
	// vectorLeft = FVector(-1.0f,0.0f,0.0f);
}

FString APlayerPawn::VectorToString(const FVector& vector)
{
	return FString("(") + FString::SanitizeFloat(vector.X) + ", " + FString::SanitizeFloat(vector.Y) + ", " + FString::SanitizeFloat(vector.Z) + ")";
}