// Fill out your copyright notice in the Description page of Project Settings.

#include "BeautyKilledTheBeast.h"
#include "EnemyEndNotify.h"


UEnemyEndNotify::UEnemyEndNotify()
{

}

void UEnemyEndNotify::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	EnemyChar = Cast<AEnemyCharacter>(MeshComp->GetOwner());
	if (EnemyChar)
	{
		EnemyChar->bIsAttacking = false;
	}
}
