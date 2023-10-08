// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class ELEMENTALDEFENDER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckDistanceOfProjectile();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true")) UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere) class UProjectileMovementComponent* movementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere) float damage = 50.f;

	UPROPERTY(EditAnywhere) float projectileMaxDistance = 10000.f;

	UPROPERTY(EditAnywhere) float projectileMaxSpeed = 10000.f;

	UPROPERTY(EditAnywhere) float projectileInitialSpeed = 10000.f;
};
