// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CodeTest/Types/SpeedMode.h"
#include "CodeTest/Interfaces/AttackableInterface.h"
#include "CombatCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCombatComponent;

UCLASS()
class CODETEST_API ACombatCharacter : public ACharacter, public IAttackableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	UCombatComponent* GetCombat_Implementation() const;

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Pressed
	UFUNCTION(BlueprintCallable)
	virtual void AttackButtonPressed();

	virtual void SprintButtonPressed();

	// Released
	virtual void SprintButtonReleased();
	
	// Axises
	virtual void MoveForward(float value);
	virtual void MoveRight(float value);
	virtual void LookUp(float value);
	virtual void Turn(float value);

private:
	UPROPERTY(VisibleAnywhere, Category = Camera);
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera);
	UCameraComponent* FollowCamera;

	UPROPERTY()
	ESpeedMode SpeedMode;

	UPROPERTY(EditAnywhere, Category = Movement)
	float SprintSpeed = 900.f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float JogSpeed = 500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComponent;

public:	
	FORCEINLINE UFUNCTION(BlueprintCallable) UCombatComponent* GetCombatComponent() const { return CombatComponent; }

	

};
