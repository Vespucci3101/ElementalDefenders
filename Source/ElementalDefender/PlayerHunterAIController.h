// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAIController.h"
#include "ElementalCharacter.h"
#include "PlayerHunterAIController.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALDEFENDER_API APlayerHunterAIController : public ABaseAIController
{
	GENERATED_BODY()

public:
    bool ReachTarget = true;
    float ElapsedTime = 0.f;
    float AngleOfVision = 120.0f;
    AElementalCharacter* ChasedPlayer = nullptr;
    UPROPERTY(EditAnywhere) float MaxAgentVision = 2000.f;
    UPROPERTY(EditAnywhere) float AgentDamage = 10.f;
    UPROPERTY(EditAnywhere) float RangeToPlayerDealingDamage = 100.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsAttacking = false;

    APlayerHunterAIController();
    virtual void Tick(float deltaTime) override;
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

    void HandleDestruction();

private:
    float CosAngleOfVision = 0.f;

    void GoToBestTarget(float deltaTime);
    float CalculateDistance(FVector OriginLocation, FVector DestLocation);
    void UpdatePlayerInteraction(float deltaTime);
    FVector FindPlayerInFieldOfView(TArray<AActor*> foundActors);
    FVector GetClosestPLayer(TArray<AActor*> foundActors);
    FVector Patrol();
    void DealDamageToPlayer(AActor* OtherActor);
    bool IsInRangeToPlayer(AActor* PlayerActor);
};
