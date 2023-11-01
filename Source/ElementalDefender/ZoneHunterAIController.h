// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.h"
#include "ZoneHunterAIController.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALDEFENDER_API AZoneHunterAIController : public ABaseAIController
{
	GENERATED_BODY()
	
public:
    bool ReachedTarget = true;
    float ElapsedTime = 0.f;
    UPROPERTY(EditAnywhere) float AgentDamage = 10.f;
    UPROPERTY(EditAnywhere) float RangeToZoneDealingDamage = 500.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsAttacking = false;

    AZoneHunterAIController();
    virtual void Tick(float deltaTime) override;
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

    void HandleDestruction();

private:
    void GoToBestTarget(float deltaTime);
    float CalculateDistance(FVector OriginLocation, FVector DestLocation);
    void UpdatePlayerInteraction(float deltaTime);
    void DealDamageToZone(AActor* OtherActor);
    bool IsInRangeToZone(AActor* ZoneActor);
    FVector Patrol();
};
