// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"

// Sets default values
AItem::AItem(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isTreasure = false;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cube(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	mesh->SetStaticMesh(cube.Object);
	SetRootComponent(mesh);
	mesh->SetSimulatePhysics(true);
	mesh->SetCollisionProfileName(FName("PhysicsActor"));
}

// Called when the game starts or when spawned
void AItem::BeginPlay(){
	Super::BeginPlay();   
}

// Called every frame
void AItem::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void AItem::Init(itemTypeEnum _itemType, float _treasureValue = 0.0f) {
	itemType = _itemType;
	isTreasure = itemType == treasureSmall || itemType == treasureMedium || itemType == treasureLarge;
	treasureValue = _treasureValue;
	if (!assetDatabase) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Item missing assetDatabase"));
		return;
	}
	
	const FString& rowString = FString(ItemTypeToString(itemType)); 
	FName rowName = FName(*rowString);
	FAssetDatabaseStruct* assetDatabaseEntry = assetDatabase->FindRow<FAssetDatabaseStruct>(rowName, rowString, true);
	#pragma region Error Handling
	if (!assetDatabaseEntry) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Item missing assetDatabaseEntry"));
		return;
	}
	if (!assetDatabaseEntry->mesh) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Item missing assetDatabaseEntry.Mesh"));
		return;
	}
	if (!assetDatabaseEntry->material) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Item missing assetDatabaseEntry.Material"));
		return;
	}
	#pragma endregion
	mesh->SetStaticMesh(assetDatabaseEntry->mesh);
	mesh->SetMaterial(0, assetDatabaseEntry->material);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, *FString().Printf(TEXT("Item Spawned: %s"), *ItemTypeToString(itemType)));
}

FString AItem::ItemTypeToString(itemTypeEnum itemType) {
	switch (itemType) {
		case treasureSmall: { return "treasureSmall"; }
		case treasureMedium: { return "treasureMedium"; }
		case treasureLarge: { return "treasureLarge"; }
		case toolkit: { return "toolkit"; }
		case cannonball: { return "cannonball"; }
		default: { return "itemMaterial"; }
	}
}

AItem::itemTypeEnum AItem::GetItemType() const { return itemType; }

bool AItem::GetIsTreasure() const { return isTreasure; }

float AItem::GetTreasureValue() const { return isTreasure ? treasureValue : 0.0f; }

void AItem::SetAssetDatabase(UDataTable* _assetDatabase) {
	assetDatabase = _assetDatabase;	
}


