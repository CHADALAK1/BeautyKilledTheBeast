// Fill out your copyright notice in the Description page of Project Settings.

#include "BeautyKilledTheBeast.h"
#include "GruntAnimInstanceClass.h"

UGruntAnimInstanceClass::UGruntAnimInstanceClass()
{

}

void UGruntAnimInstanceClass::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EnemyChar = Cast<AEnemyCharacter>(TryGetPawnOwner());
}

void UGruntAnimInstanceClass::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!EnemyChar) return;

	Speed = EnemyChar->GetVelocity().Size();
	bIsInAir = EnemyChar->GetCharacterMovement()->IsFalling();
	bIsAttacking = EnemyChar->bIsAttacking;
}
