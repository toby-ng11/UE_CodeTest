// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "CodeTest/MyComponents/CombatComponent.h"

// Sets default values
ACombatCharacter::ACombatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Character Configs
	bUseControllerRotationPitch = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->GravityScale = 1.75f;
	GetCharacterMovement()->AirControl = 0.35f;

	// Components
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}

// Called to bind functionality to input
void ACombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Actions
	// Pressed
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACombatCharacter::AttackButtonPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACombatCharacter::SprintButtonPressed);

	//Release
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACombatCharacter::SprintButtonReleased);

	//Axises
	PlayerInputComponent->BindAxis("MoveForward", this, &ACombatCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACombatCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACombatCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ACombatCharacter::Turn);
}

void ACombatCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (CombatComponent)
	{
		CombatComponent->SetCharacter(this);
	}
}

UCombatComponent* ACombatCharacter::GetCombat_Implementation() const
{
	return CombatComponent;
}

// Called when the game starts or when spawned
void ACombatCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpeedMode = ESpeedMode::ESM_Jog;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	
}

void ACombatCharacter::AttackButtonPressed()
{
	CombatComponent->RequestAttack();
}

void ACombatCharacter::SprintButtonPressed()
{
	SpeedMode = ESpeedMode::ESM_Sprint;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ACombatCharacter::SprintButtonReleased()
{
	SpeedMode = ESpeedMode::ESM_Jog;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
}

void ACombatCharacter::MoveForward(float value)
{
	// Yaw Roll
	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, ControlRotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void ACombatCharacter::MoveRight(float value)
{
	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, ControlRotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void ACombatCharacter::LookUp(float value)
{
	// Pitch
	AddControllerPitchInput(value);
}

void ACombatCharacter::Turn(float value)
{
	// Yaw
	AddControllerYawInput(value);
}

// Called every frame
/*void ACombatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/



