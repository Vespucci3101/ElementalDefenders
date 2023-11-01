// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlameThrowerAbility.generated.h"

UCLASS()
class ELEMENTALDEFENDER_API AFlameThrowerAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlameThrowerAbility();
	FDateTime StartTime;
	
	float ElapsedTime = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DealDamage();

	UPROPERTY(EditAnywhere) float AbilityMaxTime = 5.f;

	UPROPERTY(EditAnywhere) float damage = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") UStaticMeshComponent* FlamethrowerMesh;
};
