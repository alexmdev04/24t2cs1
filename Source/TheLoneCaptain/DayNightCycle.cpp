// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycle.h"

#include "Components/LightComponent.h"

// Sets default values for this component's properties
UDayNightCycle::UDayNightCycle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UDayNightCycle::BeginPlay()
{
	Super::BeginPlay();
	startingSunAngle = this->GetOwner()->GetActorRotation().Euler().Y;
	currentSunAngle = startingSunAngle;
}


// Called every frame
void UDayNightCycle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UDayNightCycle::currentSunAngle += DeltaTime;
	this->GetOwner()->SetActorRotation(FRotator(currentSunAngle,0.0f,0.0f).Quaternion()); 
}