// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ElementalCharacter.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AElementalCharacter::StaticClass(), ListActor);
    Super::Tick(DeltaTime);
    if (ListActor.Num() > 0) {

            FVector PlayerLocation = ListActor[0]->GetActorLocation();
            FVector EnemyLocation = GetActorLocation();

            // Calculez la direction du joueur vers l'ennemi
            FVector DirectionToPlayer = (PlayerLocation - EnemyLocation).GetSafeNormal();

       // Déplacez l'ennemi vers le joueur avec une certaine vitesse
       FVector NewLocation = EnemyLocation + DirectionToPlayer * EnemySpeed * DeltaTime;
       SetActorLocation(NewLocation);

    }
}



// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::HandleDestruction()
{
	Destroy();
}