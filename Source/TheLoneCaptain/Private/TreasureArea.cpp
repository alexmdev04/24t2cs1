// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureArea.h"

// Sets default values
ATreasureArea::ATreasureArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	treasureAreaCollider = CreateDefaultSubobject<UBoxComponent>(FName("treasureAreaCollider"));
	treasureAreaCollider->SetBoxExtent(FVector(100.0f, 100.0f, 25.0f));
	treasureAreaCollider->SetCollisionProfileName(TEXT("OverlapAll"));
	
	debugBox = CreateDefaultSubobject<UStaticMeshComponent>(FName("debugBox"));
	debugBox->SetupAttachment(treasureAreaCollider);
	debugBox->SetWorldScale3D(UE::Math::TVector<double>(2.0f, 2.0f, 0.5f));
	//debugBox->GetComponentTransform().TransformPosition(UE::Math::TVector<double>(0.0f,0.0f,-25.0f));
	debugBox->GetRelativeTransform().SetLocation(UE::Math::TVector<double>(0.0f,0.0f,-25.0f));
	debugBox->SetCollisionProfileName(TEXT("NoCollision"));
	debugBox->SetGenerateOverlapEvents(false);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	debugBox->SetStaticMesh(CubeMesh.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial> CubeMaterial(TEXT("/Game/World/debugZoneMaterial.debugZoneMaterial"));
	debugBox->SetMaterial(0, CubeMaterial.Object);
}	

// Called when the game starts or when spawned
void ATreasureArea::BeginPlay()
{
	Super::BeginPlay();
	treasureAreaCollider->OnComponentBeginOverlap.AddDynamic(this, &ATreasureArea::OverlapBegin);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Hello C++"));
}

// Called every frame
void ATreasureArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATreasureArea::OverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor->Tags.Contains(FName("treasure")))
	{
		otherComponent->SetPhysicsLinearVelocity(FVector(0.0f,0.0f,0.0f));
		otherActor->SetActorLocation(FVector(0.0f, 0.0f, 2110.0f), false, nullptr, ETeleportType::TeleportPhysics);
		otherActor->SetActorRotation(FRotator(0.0f,0.0f,0.0f));
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("treasure collected!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString("non-treasure Actor entered treasure zone: ") + *otherActor->GetName());
	}
}