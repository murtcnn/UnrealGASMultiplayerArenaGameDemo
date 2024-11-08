// Fill out your copyright notice in the Description page of Project Settings.


#include "GASMultiplayerArena/GAS/Abilities/GA_Shoot.h"

#include "GASMultiplayerArena/GASMultiplayerArenaCharacter.h"
#include "GASMultiplayerArena/GASMultiplayerArenaProjectile.h"
#include "GASMultiplayerArena/TP_WeaponComponent.h"
#include "GASMultiplayerArena/Weapons/PickUpRifle.h"
#include "Kismet/GameplayStatics.h"

class UTP_WeaponComponent;

UGA_Shoot::UGA_Shoot()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Rifle")));
}

void UGA_Shoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Get and check the character.
	Character = Cast<AGASMultiplayerArenaCharacter>(ActorInfo->AvatarActor);
	if (Character == nullptr || Character->GetController() == nullptr) return;
	
	// Get and the weapon component from the weapon actor that gets attached to the player when the character gets the shoot ability.
	TArray<AActor*> CharacterAttachedActors;
	Character->GetAttachedActors(CharacterAttachedActors);
	
	// Get the weapon actor attached to the player.
	AActor** WeaponActor = CharacterAttachedActors.FindByPredicate([](AActor* Actor)
	{return Actor && Actor->IsA(APickUpRifle::StaticClass());});
	if (!WeaponActor) return;

	// Get and check the weapon component from the found attached actor.
	WeaponComponent = (*WeaponActor)->GetComponentByClass<UTP_WeaponComponent>();
	if (!WeaponComponent) return;
	

	ProjectileClass = WeaponComponent->ProjectileClass;
	
	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = Character->GetActorLocation() + SpawnRotation.RotateVector(WeaponComponent->MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<AGASMultiplayerArenaProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	
	// Try and play the sound if specified
	if (WeaponComponent->FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, WeaponComponent->FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (WeaponComponent->FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(WeaponComponent->FireAnimation, 1.f);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
