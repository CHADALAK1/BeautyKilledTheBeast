// Fill out your copyright notice in the Description page of Project Settings.

#include "BeautyKilledTheBeast.h"
#include "EndNotify.h"


UEndNotify::UEndNotify()
{

}

void UEndNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
	Super::Notify(MeshComp, Animation);

	BKTBCharacter = Cast<ABeautyKilledTheBeastCharacter>(MeshComp->GetOwner());
	if (BKTBCharacter)
	{
		BKTBCharacter->bIsAttacking = false;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "NO CHAR");
	}
}

