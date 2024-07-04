// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSpawner.h"
#include "Item.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> assetDatabaseImport(TEXT("/Game/AssetDatabase.AssetDatabase"));
	assetDatabase = assetDatabaseImport.Object;
	if (!assetDatabase) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("assetDatabase Import Fail"));
		return;
	}
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemSpawner::SpawnItem(AItem::itemTypeEnum itemType, const FVector& location, const FRotator& rotation)
{
	// FActorSpawnParameters params;
	// params.Name = FName(*AItem::ItemTypeToString(itemType));
	// params.Name = FName("yo");

	AActor* itemNewActor = GetWorld()->SpawnActor(AItem::StaticClass(), &location, &rotation);
	AItem* itemNew = static_cast<AItem*>(itemNewActor);
	
	float treasureValue;
	switch (itemType) {
		case AItem::treasureSmall: { treasureValue = treasureSmallValue; break;}
		case AItem::treasureMedium:	{ treasureValue = treasureSmallValue; break;}
		case AItem::treasureLarge: { treasureValue = treasureSmallValue; break; }
		default: { treasureValue = 0.0f; break;}
	}
	itemNew->SetAssetDatabase(assetDatabase);
	itemNew->Init(itemType, treasureValue);
	ItemsSpawned.Add(itemNew);
}

// Called every frame
void AItemSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentGameTime += DeltaTime;
	
	if (currentGameTime > 5.0f)	{
		currentGameTime = 0.0f;
		SpawnItem(
			static_cast<AItem::itemTypeEnum>(FMath::RandRange(0, 5)),
			FVector(0.0f, 0.0f, 2200.0f));
	}
}