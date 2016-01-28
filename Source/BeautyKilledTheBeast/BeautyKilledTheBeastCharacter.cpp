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

void ABeautyKilledTheBeastCharacter::BeginPlay()
{
	AWeapon *Weap = GetWorld()->SpawnActor<AWeapon>(TempWeap);
	Weap->AttachRootComponentTo(GetMesh(), "WeapSocket", EAttachLocation::SnapToTarget);
}

FHitResult ABeautyKilledTheBeastCharacter::Trace(const FVector & TraceFrom, const FVector & TraceTo) const
{

	static FName WallTraceTag = FName(TEXT("WallTrace"));

	FCollisionQueryParams TraceParams(WallTraceTag, true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.AddIgnoredActor(this);

	FHitResult Hit(ForceInit);

	GetWorld()->LineTraceSingleByChannel(Hit, TraceFrom, TraceTo, WALL_TRACE, TraceParams);

	return Hit;
}

void ABeautyKilledTheBeastCharacter::ProcessWallTrace(const FHitResult & Impact, const FVector & Origin, const FVector & Dir)
{
	const FVector EndTrace = Origin + Dir * 50;
	const FVector Endpoint = Impact.GetActor() ? Impact.ImpactPoint : EndTrace;

	AStaticMeshActor *Wall = Cast<AStaticMeshActor>(Impact.GetActor());
	if (Wall)
	{
		if (Wall->ActorHasTag("Wall"))
		{
			bCanWallJump = true;
		}
	}
	else
	{
		bCanWallJump = false;
	}
}

void ABeautyKilledTheBeastCharacter::SetMaxHealth(int32 NewMax)
{
    MaxHealth = NewMax;
}

void ABeautyKilledTheBeastCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	WallCheck();

}

void ABeautyKilledTheBeastCharacter::SetHealth(int32 NewHealth)
{
	if (NewHealth <= MaxHealth || NewHealth >= 0)
	{
		Health = NewHealth;
	}
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

void ABeautyKilledTheBeastCharacter::WallCheck()
{
	const FVector Start = GetMesh()->GetSocketLocation("WallSocket");
	const FVector Dir = GetMesh()->GetSocketRotation("WallSocket").Vector();
	const FVector End = Start + Dir * 40;
	const FHitResult Impact = Trace(Start, End);
	DrawDebugLine(GetWorld(), Start, End, FColor::Green);

	ProcessWallTrace(Impact, Start, Dir);

}

void ABeautyKilledTheBeastCharacter::MeleeAttack()
{
	bIsAttacking = true;
}

void ABeautyKilledTheBeastCharacter::Dash()
{
    if(CanDash())
    {
        GetCharacterMovement()->Velocity += GetCapsuleComponent()->GetForwardVector() * 3000.f;
        DashCooldown();
    }
}

void ABeautyKilledTheBeastCharacter::JumpAction()
{
	if (!CanWallJump())
	{
		Jump();
	}
	else
	{
		if (GetCharacterMovement()->IsFalling())
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "WallJump");
			GetController()->DisableInput(GetWorld()->GetFirstPlayerController());
			LaunchCharacter((GetActorUpVector() * 1000 + GetActorForwardVector() * -1000), false, true);
			SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 180, GetActorRotation().Roll));
			GetController()->EnableInput(GetWorld()->GetFirstPlayerController());
		}
		else
		{
			Jump();
		}
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
    //Destroy(this);
}

void ABeautyKilledTheBeastCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

