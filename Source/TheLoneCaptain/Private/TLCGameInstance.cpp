// Fill out your copyright notice in the Description page of Project Settings.

#include "TLCGameInstance.h"
#include "ItemSpawner.h"

void UTLCGameInstance::Init()
{
	Super::Init();
	ItemSpawner = static_cast<AItemSpawner*>(GetWorld()->SpawnActor(AItemSpawner::StaticClass()));
}
