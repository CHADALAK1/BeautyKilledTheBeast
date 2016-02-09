// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyCharacter.h"
#include "GruntCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BEAUTYKILLEDTHEBEAST_API AGruntCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<AWeapon> Weap;

	virtual void BeginPlay() override;
	
};
