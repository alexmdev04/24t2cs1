// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TreasureArea.generated.h"

UCLASS()
class THELONECAPTAIN_API ATreasureArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreasureArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* treasureAreaCollider;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* debugBox;
// component overlap
private:	
	UFUNCTION()
	void OverlapBegin(
		UPrimitiveComponent* overlappedComponent,	
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 otherBodyIndex,
		bool bFromSweep,
		const FHitResult& sweepResult);
};
