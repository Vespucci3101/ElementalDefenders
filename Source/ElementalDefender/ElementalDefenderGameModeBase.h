// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ElementalDefenderGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALDEFENDER_API AElementalDefenderGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* actorDied);

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
