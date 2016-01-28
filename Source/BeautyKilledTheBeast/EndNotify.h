// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndNotify.generated.h"

/**
 * 
 */
UCLASS()
class BEAUTYKILLEDTHEBEAST_API UEndNotify : public UAnimNotify
{
	GENERATED_BODY()
	
	class ABeautyKilledTheBeastCharacter *BKTBCharacter;
	
public:

	UEndNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
