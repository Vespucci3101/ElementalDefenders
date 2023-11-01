// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAIController.h"

/**
 * 
 */
class ELEMENTALDEFENDER_API AIGroupManager
{
public:
	static AIGroupManager* GetInstance();
	void RegisterAgent(ABaseAIController* AIController);
	void UnregisterAgent(ABaseAIController* AIController);
	int GetAgentIndex(ABaseAIController* AIController);
	void IncrementShift();
	int Shift = 0;
	int AgentsGroupDivider = 10;

	UFUNCTION(BlueprintCallabe) void ResetAgentList();

private:
	static AIGroupManager* m_AIGroupManagerInstance;
	TArray<ABaseAIController*> m_RegisteredAgents;
};
