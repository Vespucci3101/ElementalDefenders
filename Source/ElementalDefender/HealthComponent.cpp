// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ElementalDefenderGameModeBase.h"
#include "Enemy.h"
#include "ElementalCharacter.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	health = maxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	ElementalDefenderGameModeBase = Cast<AElementalDefenderGameModeBase>(UGameplayStatics::GetGameMode(this));
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	health -= Damage;
	
	if (health < 0) health = 0.f;
	if (health > maxHealth) health = maxHealth;

	if (health <= 0.f && ElementalDefenderGameModeBase)
	{
		IsDead = true;
		ElementalDefenderGameModeBase->ActorDied(DamageActor);
	}

}

void UHealthComponent::RegenerateHealth(float healthGain, AActor* otherActor)
{
	UGameplayStatics::ApplyDamage(otherActor, -1 * healthGain, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
}