// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGroupManager.h"

AIGroupManager* AIGroupManager::m_AIGroupManagerInstance;

AIGroupManager* AIGroupManager::GetInstance()
{
	if (!m_AIGroupManagerInstance)
	{
		m_AIGroupManagerInstance = new AIGroupManager();
	}
	return m_AIGroupManagerInstance;
}

void AIGroupManager::RegisterAgent(ABaseAIController* AIController)
{
	AIController->IsAgentRegistered = true;
	m_RegisteredAgents.Emplace(AIController);
}

void AIGroupManager::UnregisterAgent(ABaseAIController* AIController)
{
	AIController->IsAgentRegistered = false;
	m_RegisteredAgents.Remove(AIController);
}

int AIGroupManager::GetAgentIndex(ABaseAIController* AIController)
{
	int idx = -1;
	bool found = m_RegisteredAgents.Find(AIController, idx);

	return found ? idx : -1;
}

void AIGroupManager::IncrementShift()
{
	Shift++;
	if (Shift >= AgentsGroupDivider) Shift = 0;
}

void AIGroupManager::ResetAgentList()
{
	m_RegisteredAgents.Empty();
}