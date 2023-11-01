// Fill out your copyright notice in the Description page of Project Settings.


#include "MeteorAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"

// Sets default values
AMeteorAbility::AMeteorAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeteorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Meteor Mesh"));
	RootComponent = MeteorMesh;
}

// Called when the game starts or when spawned
void AMeteorAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeteorAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeteorAbility::DealDamage()
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