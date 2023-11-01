// Fill out your copyright notice in the Description page of Project Settings.


#include "ZoneHunterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "AIGroupManager.h"
#include "HealthComponent.h"
#include "Zone.h"
#include "NavigationSystem.h"

AZoneHunterAIController::AZoneHunterAIController()
{

}

void AZoneHunterAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	UpdatePlayerInteraction(deltaTime);
}

void AZoneHunterAIController::UpdatePlayerInteraction(float deltaTime)
{
	ElapsedTime += deltaTime;

	AIGroupManager* m_AIGroupManagerInstance = AIGroupManager::GetInstance();

	if (m_AIGroupManagerInstance && !IsAgentRegistered) m_AIGroupManagerInstance->RegisterAgent(this);

	if (!IsAgentRegistered) return;
	
	int idx = m_AIGroupManagerInstance->GetAgentIndex(this);

	// Only the one agent has the role to increase the shift
	if (m_AIGroupManagerInstance && idx == 0) m_AIGroupManagerInstance->IncrementShift();

	if (m_AIGroupManagerInstance && idx % m_AIGroupManagerInstance->AgentsGroupDivider == m_AIGroupManagerInstance->Shift)
	{
		GoToBestTarget(deltaTime);
	}
}

void AZoneHunterAIController::GoToBestTarget(float deltaTime)
{
	APawn* AgentPawn = GetPawn();
	if (AgentPawn == nullptr) return;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZone::StaticClass(), FoundActors);

	if (FoundActors.IsEmpty()) return;

	TArray<AActor*> ActivatedZones;
	for (AActor* actor : FoundActors)
	{
		if (AZone* zoneActor = Cast<AZone>(actor))
		{
			if (zoneActor->IsActivated) ActivatedZones.Add(actor);
		}
	}

	if (ActivatedZones.IsEmpty() && ReachedTarget)
	{
		ReachedTarget = false;
		MoveTo(Patrol());
		return;
	}
	else if (ActivatedZones.IsEmpty() && !ReachedTarget) return;

	FVector TargetLocation = FVector();
	AActor* ZoneActor = ActivatedZones[0];

	float minDist = INT_MAX;
	for (AActor* actor : ActivatedZones)
	{	
		float distance = CalculateDistance(AgentPawn->GetActorLocation(), actor->GetActorLocation());
		if (distance < minDist)
		{
			minDist = distance;
			TargetLocation = actor->GetActorLocation();
			ZoneActor = actor;
		}
	}

	MoveTo(TargetLocation);

	if (ZoneActor && ElapsedTime >= 1.f)
	{
		DealDamageToZone(ZoneActor);
		ElapsedTime = 0.f;
	}
}

void AZoneHunterAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	ReachedTarget = true;
}

float AZoneHunterAIController::CalculateDistance(FVector OriginLocation, FVector DestLocation)
{
	return FVector::Dist(OriginLocation, DestLocation);
}

void AZoneHunterAIController::DealDamageToZone(AActor* OtherActor)
{
	APawn* AgentPawn = GetPawn();
	if (AgentPawn == nullptr || OtherActor == nullptr) return;

	if (!IsInRangeToZone(OtherActor)) return;

	if (OtherActor && OtherActor != this && OtherActor != AgentPawn)
	{
		IsAttacking = true;
		UGameplayStatics::ApplyDamage(OtherActor, AgentDamage, AgentPawn->GetInstigatorController(), this, UDamageType::StaticClass());
	}
}

bool AZoneHunterAIController::IsInRangeToZone(AActor* ZoneActor)
{
	APawn* AgentPawn = GetPawn();
	if (AgentPawn == nullptr || ZoneActor == nullptr) return false;

	return FVector::Dist(AgentPawn->GetActorLocation(), ZoneActor->GetActorLocation()) < RangeToZoneDealingDamage;
}

FVector AZoneHunterAIController::Patrol()
{
	APawn* AgentPawn = GetPawn();
	if (AgentPawn == nullptr) return FVector(-1, -1, -1);

	FNavLocation result;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	bool ok = NavSystem->GetRandomReachablePointInRadius(AgentPawn->GetActorLocation(), 4000.f, result);

	if (ok) return result;
	return FVector(-1, -1, -1);
}

void AZoneHunterAIController::HandleDestruction()
{
	APawn* AgentPawn = GetPawn();
	if (AgentPawn != nullptr) AgentPawn->Destroy();

	AIGroupManager* m_AIGroupManagerInstance = AIGroupManager::GetInstance();
	if (m_AIGroupManagerInstance && IsAgentRegistered) m_AIGroupManagerInstance->UnregisterAgent(this);

	Destroy();
}