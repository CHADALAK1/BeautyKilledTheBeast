// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BeautyKilledTheBeastCharacter.generated.h"

UCLASS(config=Game)
class ABeautyKilledTheBeastCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
    
public:
    
    /** Does Melee Attack for Character */
    UFUNCTION(BlueprintCallable, Category = Controls)
    void MeleeAttack();
    
    /** Dashes Character in forward direction */
    UFUNCTION(BlueprintCallable, Category = Controls)
    void Dash();
    
    UFUNCTION(BlueprintCallable, Category = Health)
    float GetHealthPercentage();
    
    /** Removes or "Kills" Character */
    void Kill();
    
    /** Sets Health for the Character
     * @param NewHealth  Sets new health for the character
     */
    void SetHealth(int32 NewHealth);
    
    /** Decreases Health from character
     * @param Add Added value of health
     */
    void AddHealth(int32 Add);
    
    /** Decreases Health from Character
     * @param Decrease  Decreases value of health
     */
    void DecreaseHealth(int32 Decrease);
    
    /** Sets the MaxHealth value
     * @param NewMax  New MaxHealth value to be assigned
     */
    void SetMaxHealth(int32 NewMax);
    
private:
    
    /** tells whether the Character can dash or not */
    bool bCanDash;
    
    /** Health for Character */
    int32 Health;
    
    /** Max Health for Character */
    int32 MaxHealth;
    
    /** Timer Handle for the Cooldown on Dash */
    FTimerHandle THDashCooldown;

protected:
    
    /** Starts Cooldown for the dash ability */
    void DashCooldown();
    
    /** Re-Enables Dash after cooldown */
    void EnableDash();

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	ABeautyKilledTheBeastCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    /** Returns bIsDashing boolean **/
    FORCEINLINE bool CanDash() const { return bCanDash; }
    /** Returns Health integer value **/
    FORCEINLINE int32 GetHealth() const { return Health; }
    /**Returns MaxHealth integer value **/
    FORCEINLINE int32 GetMaxHealth() const { return MaxHealth; }
};
