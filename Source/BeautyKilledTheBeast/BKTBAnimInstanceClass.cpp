// Fill out your copyright notice in the Description page of Project Settings.

#include "BeautyKilledTheBeast.h"
#include "BKTBAnimInstanceClass.h"

UBKTBAnimInstanceClass::UBKTBAnimInstanceClass()
{

}

void UBKTBAnimInstanceClass::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BKTBCharacter = Cast<ABeautyKilledTheBeastCharacter>(TryGetPawnOwner());
}

void UBKTBAnimInstanceClass::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!BKTBCharacter) return;

	bIsAttacking = BKTBCharacter->bIsAttacking;
	bIsInAir = BKTBCharacter->GetMovementComponent()->IsFalling();
	Speed = BKTBCharacter->GetVelocity().Size();
}

void UBKTBAnimInstanceClass::SetDirectionAndSpeed(float & OutDirection, float & OutSpeed)
{
}

