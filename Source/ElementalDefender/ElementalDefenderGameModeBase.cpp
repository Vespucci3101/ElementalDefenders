// Copyright Epic Games, Inc. All Rights Reserved.


#include "ElementalDefenderGameModeBase.h"
#include "Enemy.h"

void AElementalDefenderGameModeBase::ActorDied(AActor* DeadActor)
{
	if (AEnemy* destroyedEnemy = Cast<AEnemy>(DeadActor))
	{
		destroyedEnemy->HandleDestruction();
	}
}