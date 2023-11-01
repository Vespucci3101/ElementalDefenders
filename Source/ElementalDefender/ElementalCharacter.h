// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ElementalCharacter.generated.h"

UCLASS()
class ELEMENTALDEFENDER_API AElementalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AElementalCharacter();

	UPROPERTY(BlueprintReadonly) bool jumping = false;
	UPROPERTY(BlueprintReadonly) bool IsMovingForward = false;
	UPROPERTY(BlueprintReadonly) bool IsMovingRight = false;
	UPROPERTY(BlueprintReadonly) bool IsMovingForwardOrBackward = false;
	UPROPERTY(BlueprintReadonly) bool IsMovingRightOrLeft = false;
	float PlayerSpeed = 5000.f;
	FVector CurrentVelocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveLeftRight(float AxisValue);
	void MouseX(float AxisValue);
	void MouseY(float AxisValue);
	void CheckJump();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera") USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera") UCameraComponent* CameraComponent;
};
