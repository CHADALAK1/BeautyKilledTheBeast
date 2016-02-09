// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BeautyKilledTheBeastCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BEAUTYKILLEDTHEBEAST_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:

	AEnemyCharacter();

	UFUNCTION(BlueprintCallable, Category = Attack)
	void Attack();

	UFUNCTION(BlueprintCallable, Category = HealthBar)
	float GetHealthPercentage();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharConditions")
	uint32 bIsAttacking : 1;

private:

	int32 Health;

	int32 MaxHealth;

public:

	FORCEINLINE int32 GetHealth() const { return Health; }
	FORCEINLINE int32 GetMaxHealth() const { return MaxHealth; }
	
};
