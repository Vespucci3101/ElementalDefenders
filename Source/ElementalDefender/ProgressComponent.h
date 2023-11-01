// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProgressComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELEMENTALDEFENDER_API UProgressComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProgressComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) float maxProgress = 100.f;
	UPROPERTY(BlueprintReadOnly) float currentProgress = 0.f;
	UPROPERTY(BlueprintReadOnly) bool isProgressStarted = false;

	UFUNCTION(BlueprintCallable) void StartProgress();
	UFUNCTION(BlueprintCallable) void ResetProgress();

	void IncrementProgress(int nbOfPlayers);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
