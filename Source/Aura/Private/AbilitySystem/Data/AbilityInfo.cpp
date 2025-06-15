// Copyright JackK


#include "AbilitySystem/Data/AbilityInfo.h"
#include "AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for(const FAuraAbilityInfo& AbilityInfo : AbilityInformation)
	{
		if (AbilityInfo.AbilityTag == AbilityTag)
		{
			return AbilityInfo;
		}
	}
	
	if (bLogNotFound) {
		UE_LOG(LogAura, Error, TEXT("no info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAbilityInfo();
}
