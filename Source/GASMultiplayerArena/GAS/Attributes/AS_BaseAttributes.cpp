// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffectExtension.h"
#include "GASMultiplayerArena/GAS/Attributes/AS_BaseAttributes.h"

UAS_BaseAttributes::UAS_BaseAttributes()
{
	// Initialize default values for attributes
	Health = 100.0f;
	Mana = 50.0f;
	Strength = 10.0f;
}

void UAS_BaseAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Block health from going below zero.
		Health.SetCurrentValue(FMath::Max(0.0f, Health.GetCurrentValue()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Block mana from going below zero.
		Mana.SetCurrentValue(FMath::Max(0.0f, Mana.GetCurrentValue()));
	}

	if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		// Block strength from going below zero.
		Strength.SetCurrentValue(FMath::Max(0.0f, Strength.GetCurrentValue()));
	}
}
