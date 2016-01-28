// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "BKTBAnimInstanceClass.generated.h"

/**
 * 
 */
UCLASS()
class BEAUTYKILLEDTHEBEAST_API UBKTBAnimInstanceClass : public UAnimInstance
{
	GENERATED_BODY()
	
	class ABeautyKilledTheBeastCharacter* BKTBCharacter;

protected:

	UBKTBAnimInstanceClass();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Calculate character direction and speed
	UFUNCTION(BlueprintCallable, Category = "TU Character Animation")
		void SetDirectionAndSpeed(float& OutDirection, float& OutSpeed);

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint32 bIsAttacking : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint32 bIsInAir : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimationAsset *Attack;
	
	
};
