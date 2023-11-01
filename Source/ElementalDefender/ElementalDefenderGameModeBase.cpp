// Copyright Epic Games, Inc. All Rights Reserved.


#include "ElementalDefenderGameModeBase.h"
#include "Enemy.h"
#include "Zone.h"
#include "AIGroupManager.h"
#include "PlayerHunterAIController.h"
#include "ZoneHunterAIController.h"

void AElementalDefenderGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AIGroupManager* m_AIGroupManagerInstance = AIGroupManager::GetInstance();
	if (m_AIGroupManagerInstance) m_AIGroupManagerInstance->ResetAgentList();
}

void AElementalDefenderGameModeBase::ActorDied(AActor* DeadActor)
{
	if (AEnemy* destroyedEnemy = Cast<AEnemy>(DeadActor)) destroyedEnemy->HandleDestruction();
	else if (AZone* destroyedZone = Cast<AZone>(DeadActor)) destroyedZone->HandleDestruction();
	else if (APawn* AIPawn = Cast<APawn>(DeadActor)) 
	{
		if (APlayerHunterAIController* AIPlayerHunterController = Cast<APlayerHunterAIController>(AIPawn->GetController()))
		{
			AIPlayerHunterController->HandleDestruction();
		}
		else if (AZoneHunterAIController* AIZoneHunterController = Cast<AZoneHunterAIController>(AIPawn->GetController()))
		{
			AIZoneHunterController->HandleDestruction();
		}
	}
}