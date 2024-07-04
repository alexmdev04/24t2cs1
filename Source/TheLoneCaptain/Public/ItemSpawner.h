// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

UCLASS()
class THELONECAPTAIN_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
	void SpawnItem(AItem::itemTypeEnum itemType, const FVector& location = FVector(), const FRotator& rotation = FRotator());
	
	float currentGameTime = 0.0f;
	const float treasureSmallValue = 10.0f;
	const float treasureMediumValue = 50.0f;
	const float treasureLargeValue = 100.0f;
	UPROPERTY(VisibleAnywhere)
	TArray<AItem*> ItemsSpawned;
	UPROPERTY()
	UDataTable* assetDatabase;
};
