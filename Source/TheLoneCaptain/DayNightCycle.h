// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include <cstdlib>
#include "DayNightCycle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELONECAPTAIN_API UDayNightCycle : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDayNightCycle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float currentSunAngle; // can be between 0 and 359 (270 is center, 180-359 = Day, 0-179 = Night)
	float startingSunAngle = 195.0f;
	float cycleMultiplier;
};
