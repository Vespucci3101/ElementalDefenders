// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProgressComponent.h"
#include "HealthComponent.h"
#include "Zone.generated.h"

UCLASS()
class ELEMENTALDEFENDER_API AZone : public AActor
{
	GENERATED_BODY()
	
public:	
	bool IsCompleted = false;

	// Sets default values for this actor's properties
	AZone();

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsActivated = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsReset = false;
	UPROPERTY(EditAnywhere, BlueprintReadonly) float HealthRegain = 10.f;

	UPROPERTY(EditAnywhere) UMaterialInterface* InvisbleMaterial;

	UProgressComponent* ProgressComponent;

	UHealthComponent* HealthComponent;

	float ProgressElapsedTime = 0.f;

	float HealthElapsedTime = 0.f;
};
