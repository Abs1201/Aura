// Copyright JackK


#include "AbilitySystem/AuraAbilitySystemGlobals.h"
#include "AuraAbilityTypes.h"

FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}

void UAuraAbilitySystemGlobals::InitGlobalData()
{
	Super::InitGlobalData();
}
