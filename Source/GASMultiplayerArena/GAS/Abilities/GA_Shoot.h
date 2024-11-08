// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Shoot.generated.h"

class UTP_WeaponComponent;
class AGASMultiplayerArenaCharacter;
/**
 * 
 */
UCLASS()
class GASMULTIPLAYERARENA_API UGA_Shoot : public UGameplayAbility
{
	GENERATED_BODY()

private:
	UGA_Shoot();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY()
	AGASMultiplayerArenaCharacter* Character = nullptr;

	UPROPERTY()
	TSubclassOf<class AGASMultiplayerArenaProjectile> ProjectileClass = nullptr;

public:
	UPROPERTY()
	UTP_WeaponComponent* WeaponComponent = nullptr;
};
