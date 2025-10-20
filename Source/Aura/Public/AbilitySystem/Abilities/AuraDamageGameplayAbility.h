// Copyright JackK

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraAbilityTypes.h"

#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
//starting in lec 158
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	//lec 182
public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	//305
	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr) const;

	UFUNCTION(BlueprintPure)
	float GetDamageAtLevel() const;
protected:
	// lec 124
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	////lec 135 
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	//FScalableFloat Damage;

	//UPROPERTY(EditDefaultsOnly, Category = "Damage")
	//TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;
	//304
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffChance = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDamage = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffFrequency = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDuration = 5.f;
	//312. adding impulse
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DeathImpulseMagnitude = 1000.f;
	//315. Knockback
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float KnockbackForceMagnitude = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float KnockbackChance = 0.f;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
	// 295
	//float GetDamageByDamageType(float InLevel, const FGameplayTag& DamageType);
};
