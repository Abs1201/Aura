// Copyright JackK

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

// start in lec 86
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	// lec 159
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	
	// lec 134. Set by caller _ since this 'Magnitude Calc type' is Key-value pair.
	FGameplayTag Damage;
	//lec 158
	FGameplayTag Damage_Fire;
	//159
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;

	//lec 177.Melee Attack
	FGameplayTag Abilities_Attack;
	//224
	FGameplayTag Abilities_Summon;
	//239
	FGameplayTag Abilities_Fire_FireBolt;

	// lec 184. Montage Gameplay Tag. 골렘뿐만아니라 몬스터들의 공격 소켓을 태그로 받아오기위함. ,207
	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	// 215
	FGameplayTag CombatSocket_Tail;

	//207
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;



	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;


	//136. react를 GE로 줄 줄이야..
	FGameplayTag Effects_HitReact;

protected:


private:
	static FAuraGameplayTags GameplayTags;
};