// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "EnemyEndNotify.generated.h"

/**
 * 
 */
UCLASS()
class BEAUTYKILLEDTHEBEAST_API UEnemyEndNotify : public UAnimNotify
{
	GENERATED_BODY()

	class AEnemyCharacter *EnemyChar;

public:

	UEnemyEndNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
