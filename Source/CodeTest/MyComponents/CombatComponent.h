// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CodeTest/Types/CombatStage.h"
#include "CombatComponent.generated.h"

class UAnimMontage;
class ACharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODETEST_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void RequestAttack();

	bool CanAttack();

	void PlayAnimMontage(UAnimMontage* MontageToPlay);

	UFUNCTION(BlueprintCallable)
	void ResetAttack();

	UFUNCTION(BlueprintCallable)
		void ComboAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Attack();
private:
	UPROPERTY()
	ECombatStage CombatState;
	
	UPROPERTY(EditAnywhere, Category = Animation)
	TArray<UAnimMontage*> AttackAnimMontages;

	UPROPERTY();
	ACharacter* Character;

	bool bIsReachedComboAttackPoint = false;
	int32 AttackIndex = 0;

	//Getter and setter
public:
	FORCEINLINE void SetCharacter(ACharacter* Value) { Character = Value; }
};
