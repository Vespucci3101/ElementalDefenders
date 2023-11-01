// Fill out your copyright notice in the Description page of Project Settings.


#include "BlizzardAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"

// Sets default values
ABlizzardAbility::ABlizzardAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlizzardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blizzard Mesh"));
	RootComponent = BlizzardMesh;
}

// Called when the game starts or when spawned
void ABlizzardAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlizzardAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
	if (ElapsedTime >= 1 && isDamageTriggered)
	{
		DealDamage();
		ElapsedTime = 0.f;
	}
}

void ABlizzardAbility::DealDamage()
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