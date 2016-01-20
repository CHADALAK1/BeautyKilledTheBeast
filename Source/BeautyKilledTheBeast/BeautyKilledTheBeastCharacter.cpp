// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BeautyKilledTheBeast.h"
#include "BeautyKilledTheBeastCharacter.h"

ABeautyKilledTheBeastCharacter::ABeautyKilledTheBeastCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 650.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 8196.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
    
    bCanDash = true;
    
    SetMaxHealth(100);
    Health = 75;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABeautyKilledTheBeastCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    
	InputComponent->BindAxis("MoveRight", this, &ABeautyKilledTheBeastCharacter::MoveRight);
}

void ABeautyKilledTheBeastCharacter::SetMaxHealth(int32 NewMax)
{
    MaxHealth = NewMax;
}

void ABeautyKilledTheBeastCharacter::AddHealth(int32 Add)
{
    if((GetMaxHealth() - GetHealth()) < Add)
    {
        Health += Add;
    }
    else
    {
        Health = GetMaxHealth();
    }
}

void ABeautyKilledTheBeastCharacter::DecreaseHealth(int32 Decrease)
{
    if((GetHealth() - Decrease) > 0)
    {
        Health -= Decrease;
    }
    else
    {
        Health = 0;
    }
}

float ABeautyKilledTheBeastCharacter::GetHealthPercentage()
{
    return FMath::GetRangePct(0, GetMaxHealth(), GetHealth());
}

void ABeautyKilledTheBeastCharacter::MeleeAttack()
{
    
}

void ABeautyKilledTheBeastCharacter::Dash()
{
    if(CanDash())
    {
        GetCharacterMovement()->Velocity += GetCapsuleComponent()->GetForwardVector() * 3000.f;
        DashCooldown();
    }
}

void ABeautyKilledTheBeastCharacter::DashCooldown()
{
    bCanDash = false;
    GetWorldTimerManager().SetTimer(THDashCooldown, this, &ABeautyKilledTheBeastCharacter::EnableDash, 2.f, false);
}

void ABeautyKilledTheBeastCharacter::EnableDash()
{
    bCanDash = true;
    GetWorldTimerManager().ClearTimer(THDashCooldown);
}

void ABeautyKilledTheBeastCharacter::Kill()
{
    Destroy(this);
}

void ABeautyKilledTheBeastCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

