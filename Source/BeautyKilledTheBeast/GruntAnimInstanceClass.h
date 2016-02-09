// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "GruntAnimInstanceClass.generated.h"

/**
 * 
 */
UCLASS()
class BEAUTYKILLEDTHEBEAST_API UGruntAnimInstanceClass : public UAnimInstance
{
	GENERATED_BODY()

	class AEnemyCharacter *EnemyChar;
	
protected:

	UGruntAnimInstanceClass();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInAir;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint32 bIsAttacking : 1;
	
};
