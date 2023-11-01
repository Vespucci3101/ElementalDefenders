// Fill out your copyright notice in the Description page of Project Settings.


#include "IceThrowerAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"

// Sets default values
AIceThrowerAbility::AIceThrowerAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IceThrowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ice Mesh"));
	RootComponent = IceThrowerMesh;
}

// Called when the game starts or when spawned
void AIceThrowerAbility::BeginPlay()
{
	Super::BeginPlay();
	StartTime = FDateTime::Now();
}

// Called every frame
void AIceThrowerAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((FDateTime::Now() - StartTime).GetSeconds() >= AbilityMaxTime)
	{
		Destroy();
	}

	ElapsedTime += DeltaTime;
	if (ElapsedTime >= 1)
	{
		DealDamage();
		ElapsedTime = 0;
	}
}

void AIceThrowerAbility::DealDamage()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* actor : OverlappingActors)
	{
		if (AEnemy* enemy = Cast<AEnemy>(actor))
		{
			UGameplayStatics::ApplyDamage(enemy, damage, this->GetInstigatorController(), this, UDamageType::StaticClass());
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Dealing Damage to Enemy")));
		}
	}
}