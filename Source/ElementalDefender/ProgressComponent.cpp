// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressComponent.h"

// Sets default values for this component's properties
UProgressComponent::UProgressComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProgressComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UProgressComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UProgressComponent::StartProgress()
{
	isProgressStarted = true;
}

void UProgressComponent::ResetProgress()
{
	isProgressStarted = false;
	currentProgress = 0.f;
}

void UProgressComponent::IncrementProgress(int nbOfPlayers)
{
	currentProgress += 1 * nbOfPlayers;

	if (currentProgress > maxProgress) currentProgress = maxProgress;
}