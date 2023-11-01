// Fill out your copyright notice in the Description page of Project Settings.


#include "Zone.h"
#include "ElementalCharacter.h"

// Sets default values
AZone::AZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZone::BeginPlay()
{
	Super::BeginPlay();
	
	ProgressComponent = Cast<UProgressComponent>(GetComponentByClass(UProgressComponent::StaticClass()));
	HealthComponent = Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));
}

// Called every frame
void AZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsCompleted) return;

	if (ProgressComponent->currentProgress >= 100.f)
	{
		IsCompleted = true;
		return;
	}

	ProgressElapsedTime += DeltaTime;
	HealthElapsedTime += DeltaTime;
	if (ProgressComponent && ProgressComponent->isProgressStarted && ProgressElapsedTime >= 1)
	{
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors);

		int NbOfOverlappingPlayers = 0;
		for (AActor* actor : OverlappingActors)
		{
			if (AElementalCharacter* character = Cast<AElementalCharacter>(actor))
			{
				NbOfOverlappingPlayers++;
			}
		}

		ProgressComponent->IncrementProgress(NbOfOverlappingPlayers);
		ProgressElapsedTime = 0;
	}

	if (HealthComponent && HealthComponent->health >= 100) IsReset = false;

	if (HealthComponent && IsReset && HealthElapsedTime >= 1)
	{
		HealthComponent->RegenerateHealth(HealthRegain, this);
		HealthElapsedTime = 0;
	}
}

void AZone::HandleDestruction()
{
	IsActivated = false;
	IsReset = true;
	HealthElapsedTime = 0.f;

	if (ProgressComponent) ProgressComponent->ResetProgress();

	TSet<UActorComponent*> Components = GetComponents();

	for (UActorComponent* component : Components)
	{
		if (component->GetName() == "ZoneDimensionSphere")
		{
			if (UStaticMeshComponent* componentStaticMesh = Cast<UStaticMeshComponent>(component))
			{
				componentStaticMesh->SetMaterial(0, InvisbleMaterial);
			}
		}

		if (component->GetName() == "NS_Lightning")
		{
			component->SetActive(false);
		}
	}
}