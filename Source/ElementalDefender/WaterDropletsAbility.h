// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterDropletsAbility.generated.h"

UCLASS()
class ELEMENTALDEFENDER_API AWaterDropletsAbility : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere) float ElapsedTime = 0.f;

	UPROPERTY(BlueprintReadWrite) bool isDamageTriggered = false;

	// Sets default values for this actor's properties
	AWaterDropletsAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DealDamage();

	UPROPERTY(EditAnywhere) float damage = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") UStaticMeshComponent* WaterDropletsMesh;
};
