// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeteorAbility.generated.h"

UCLASS()
class ELEMENTALDEFENDER_API AMeteorAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeteorAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable) void DealDamage();

	UPROPERTY(EditAnywhere) float damage = 500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") UStaticMeshComponent* MeteorMesh;
};
