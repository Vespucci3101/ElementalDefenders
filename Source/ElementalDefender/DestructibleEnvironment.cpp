// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleEnvironment.h"

// Sets default values
ADestructibleEnvironment::ADestructibleEnvironment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestructibleEnvironment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleEnvironment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

