// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Zone.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectileMesh;

	movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	movementComponent->MaxSpeed = projectileMaxSpeed;
	movementComponent->InitialSpeed = projectileInitialSpeed;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckDistanceOfProjectile();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* myOwner = GetOwner();
	if (myOwner == nullptr) return;
	
	if (!IsValidTarget(OtherActor))
	{
		Destroy();
		return;
	}
	
	if (OtherActor && OtherActor != this && OtherActor != myOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, damage, myOwner->GetInstigatorController(), this, UDamageType::StaticClass());
	}
	Destroy();
}

void AProjectile::CheckDistanceOfProjectile()
{
	float dist = FVector::Dist(GetActorLocation(), GetOwner()->GetActorLocation());
	if (dist >= projectileMaxDistance) Destroy();
}

bool AProjectile::IsValidTarget(AActor* OtherActor)
{
	if (AZone* zone = Cast<AZone>(OtherActor)) return false;
	return true;
}