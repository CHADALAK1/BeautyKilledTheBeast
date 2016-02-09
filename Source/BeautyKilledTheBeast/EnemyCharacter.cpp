// Fill out your copyright notice in the Description page of Project Settings.

#include "BeautyKilledTheBeast.h"
#include "EnemyCharacter.h"


AEnemyCharacter::AEnemyCharacter()
{
	Health = 40;
	MaxHealth = 40;
	bIsAttacking = false;
}

void AEnemyCharacter::Attack()
{
	bIsAttacking = true;
}

float AEnemyCharacter::GetHealthPercentage()
{
	return FMath::GetRangePct(0, GetMaxHealth(), GetHealth());
}


