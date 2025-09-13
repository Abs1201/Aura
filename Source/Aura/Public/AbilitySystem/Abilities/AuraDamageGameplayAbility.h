// Copyright JackK

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"

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

	
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
	// 295
	//float GetDamageByDamageType(float InLevel, const FGameplayTag& DamageType);
};
