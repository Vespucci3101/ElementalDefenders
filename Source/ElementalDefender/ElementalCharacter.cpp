// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementalCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "ElementalGameInstance.h"

// Sets default values
AElementalCharacter::AElementalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	jumping = false;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point Component"));
	ProjectileSpawnPoint->SetupAttachment(GetMesh());
	ProjectileSpawnPoint->SetRelativeLocation(FVector(150, 0, 0));

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	// Might have to check the rotation
	CameraSpringArm->SetRelativeRotation(FRotator(-30, 0, 0));
	CameraSpringArm->SetRelativeLocation(FVector(11, 100, 50));
	CameraSpringArm->TargetArmLength = 600;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	// Might have to check the rotation
	CameraComponent->SetRelativeRotation(FRotator(10, 0, 0));
}

// Called when the game starts or when spawned
void AElementalCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElementalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (jumping)
	{
		Jump();
	}
}

// Called to bind functionality to input
void AElementalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AElementalCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AElementalCharacter::MoveLeftRight);

	PlayerInputComponent->BindAxis("MouseX", this, &AElementalCharacter::MouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &AElementalCharacter::MouseY);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AElementalCharacter::CheckJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AElementalCharacter::CheckJump);
}

void AElementalCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * PlayerSpeed, AxisValue);
}

void AElementalCharacter::MoveLeftRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * PlayerSpeed, AxisValue);
}

void AElementalCharacter::MouseX(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AElementalCharacter::MouseY(float AxisValue)
{
	AddControllerPitchInput(AxisValue * -1);
}

void AElementalCharacter::CheckJump()
{
	if (jumping)
	{
		jumping = false;
	}
	else
	{
		jumping = true;
	}
	
}