// Fill out your copyright notice in the Description page of Project Settings.


#include "FlameThrowerAbility.h"
#include "Misc/DateTime.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"

// Sets default values
AFlameThrowerAbility::AFlameThrowerAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlamethrowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fire Mesh"));
	RootComponent = FlamethrowerMesh;
}

// Called when the game starts or when spawned
void AFlameThrowerAbility::BeginPlay()
{
	Super::BeginPlay();
	StartTime = FDateTime::Now();
}

// Called every frame
void AFlameThrowerAbility::Tick(float DeltaTime)
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

void AFlameThrowerAbility::DealDamage()
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