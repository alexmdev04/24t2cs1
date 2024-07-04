// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpawner.h"
#include "Engine/GameInstance.h"
#include "TLCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THELONECAPTAIN_API UTLCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	UPROPERTY(VisibleAnywhere)
	AItemSpawner* ItemSpawner;
};
