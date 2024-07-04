// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class THELONECAPTAIN_API AItem : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
	enum itemTypeEnum
	{
		none,
		treasureSmall,
		treasureMedium,
		treasureLarge,
		toolkit,
		cannonball
	};
	virtual void Tick(float DeltaTime) override;
	void Init(itemTypeEnum _itemType, float _treasureValue);
	static FString ItemTypeToString(itemTypeEnum itemType);
	itemTypeEnum GetItemType() const;
	bool GetIsTreasure() const;
	float GetTreasureValue() const;
	void SetAssetDatabase(UDataTable* _assetDatabase);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh;
	bool isTreasure;
	itemTypeEnum itemType = none;
	float treasureValue = 0.0f;
	//UPROPERTY(EditAnywhere, Category = "Assets", meta = (RequiredAssetDataTags = "RowStructure=/Game/AssetDatabaseEntry.AssetDatabaseEntry'"))
	UPROPERTY()
	UDataTable* assetDatabase;

};

USTRUCT(BlueprintType)
struct FAssetDatabaseStruct : public FTableRowBase {
	GENERATED_BODY();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMesh> mesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UMaterialInstance> material;
};