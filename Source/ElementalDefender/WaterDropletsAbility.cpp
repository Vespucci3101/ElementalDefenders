// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterDropletsAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"

// Sets default values
AWaterDropletsAbility::AWaterDropletsAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaterDropletsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water Mesh"));
	RootComponent = WaterDropletsMesh;
}

// Called when the game starts or when spawned
void AWaterDropletsAbility::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWaterDropletsAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
	if (ElapsedTime >= 1 && isDamageTriggered)
	{
		DealDamage();
		ElapsedTime = 0.f;
	}
}

void AWaterDropletsAbility::DealDamage()
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