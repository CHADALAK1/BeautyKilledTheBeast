// Fill out your copyright notice in the Description page of Project Settings.

#include "BeautyKilledTheBeast.h"
#include "GruntCharacter.h"


void AGruntCharacter::BeginPlay()
{
	Super::BeginPlay();

	AWeapon *NewWeap = GetWorld()->SpawnActor<AWeapon>(Weap);
	if (NewWeap)
	{
		NewWeap->AttachRootComponentTo(GetMesh(), "WeapSocket", EAttachLocation::SnapToTarget);
	}
}

