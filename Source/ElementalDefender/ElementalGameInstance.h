// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ElementalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALDEFENDER_API UElementalGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controller Index") int PlayerControllerIndex = -1;
};
