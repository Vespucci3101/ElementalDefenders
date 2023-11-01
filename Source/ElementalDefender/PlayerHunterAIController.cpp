// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHunterAIController.h"
#include "AIGroupManager.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

APlayerHunterAIController::APlayerHunterAIController()
{
	CosAngleOfVision = FMath::Cos(AngleOfVision * PI / 360);
}

void APlayerHunterAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	UpdatePlayerInteraction(deltaTime);
}

void APlayerHunterAIController::UpdatePlayerInteraction(float deltaTime)
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

void APlayerHunterAIController::GoToBestTarget(float deltaTime)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AElementalCharacter::StaticClass(), FoundActors);

	if (FoundActors.IsEmpty() && ReachTarget)
	{
		ReachTarget = false;
		MoveTo(Patrol());
	}
	else
	{
		FVector PlayerLocation = FindPlayerInFieldOfView(FoundActors);
		if (PlayerLocation != FVector(-1, -1, -1))
		{
			MoveTo(PlayerLocation);
			if (ElapsedTime >= 1.f)
			{
				DealDamageToPlayer(ChasedPlayer);
				ElapsedTime = 0;
			}
		}
		else if (ReachTarget)
		{
			ReachTarget = false;
			MoveTo(Patrol());
		}
	}
}

void APlayerHunterAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	ReachTarget = true;
}

float APlayerHunterAIController::CalculateDistance(FVector OriginLocation, FVector DestLocation)
{
	return FVector::Dist(OriginLocation, DestLocation);
}

FVector APlayerHunterAIController::FindPlayerInFieldOfView(TArray<AActor*> foundActors)
{
	FVector ClosestPlayer = GetClosestPLayer(foundActors);

	APawn* AgentPawn = GetPawn();
	if (AgentPawn == nullptr) return FVector(-1, -1, -1);

	FVector RaycastStart = AgentPawn->GetActorLocation() + (AgentPawn->GetActorForwardVector() * 200.f);
	FVector RaycastEnd = ClosestPlayer;

	// Maybe could be removed
	FHitResult playerHit;
	GetWorld()->LineTraceSingleByProfile(playerHit, RaycastStart, RaycastEnd, UCollisionProfile::BlockAll_ProfileName);

	if (!playerHit.GetActor()) return FVector(-1, -1, -1);

	float distToHit = CalculateDistance(playerHit.Location, RaycastStart);
	if (distToHit < MaxAgentVision)
	{
		FVector diff = (playerHit.GetActor()->GetActorLocation() - AgentPawn->GetActorLocation()).GetSafeNormal();
		float dot = FVector::DotProduct(diff, AgentPawn->GetActorForwardVector());

		if (dot >= CosAngleOfVision)
		{
			if (AElementalCharacter* player = Cast<AElementalCharacter>(playerHit.GetActor())) ChasedPlayer = player;
			return playerHit.Location;
		}
	}
	return FVector(-1, -1, -1);
}

FVector APlayerHunterAIController::GetClosestPLayer(TArray<AActor*> foundActors)
{
	FVector ClosestPlayer = FVector(0, 0, 0);

	APawn* AgentPawn = GetPawn();
	if (AgentPawn == nullptr) return ClosestPlayer;

	float minDist = MAX_FLT;
	for (AActor* actor : foundActors)
	{
		if (AElementalCharacter* player = Cast<AElementalCharacter>(actor))
		{
			float dist = CalculateDistance(player->GetActorLocation(), AgentPawn->GetActorLocation());
			if (dist < minDist)
			{
				minDist = dist;
				ClosestPlayer = player->GetActorLocation();
			}
		}
	}

	return ClosestPlayer;
}

FVector APlayerHunterAIController::Patrol()
{
	APawn* AgentPawn = GetPawn();
	if (AgentPawn == nullptr) return FVector(-1, -1, -1);

	FNavLocation result;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	bool ok = NavSystem->GetRandomReachablePointInRadius(AgentPawn->GetActorLocation(), 4000.f, result);

	if (ok) return result;
	return FVector(-1, -1, -1);
}

void APlayerHunterAIController::DealDamageToPlayer(AActor* OtherActor)
{
	APawn* AgentPawn = GetPawn();
	if (AgentPawn == nullptr || OtherActor == nullptr) return;

	if (!IsInRangeToPlayer(OtherActor)) return;

	if (OtherActor && OtherActor != this && OtherActor != AgentPawn)
	{
		IsAttacking = true;
		UGameplayStatics::ApplyDamage(OtherActor, AgentDamage, AgentPawn->GetInstigatorController(), this, UDamageType::StaticClass());
	}
}

bool APlayerHunterAIController::IsInRangeToPlayer(AActor* PlayerActor)
{
	APawn* AgentPawn = GetPawn();
	if (AgentPawn == nullptr || PlayerActor == nullptr) return false;

	return FVector::Dist(AgentPawn->GetActorLocation(), PlayerActor->GetActorLocation()) < RangeToPlayerDealingDamage;
}

void APlayerHunterAIController::HandleDestruction()
{
	APawn* AgentPawn = GetPawn();
	if (AgentPawn != nullptr) AgentPawn->Destroy();

	AIGroupManager* m_AIGroupManagerInstance = AIGroupManager::GetInstance();
	if (m_AIGroupManagerInstance && IsAgentRegistered) m_AIGroupManagerInstance->UnregisterAgent(this);

	Destroy();
}