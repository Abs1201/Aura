// Copyright JackK


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraGameplayTags.h"

struct AuraDamageStatics {
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor); //DECLARE_는 선언 (멤버 변수 생김), 여기서 ~Property, ~Def 생김. 그런 매크로임.
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);

	AuraDamageStatics() {
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false); //DEFINE_는 정의 (무엇을 어떻게 캡처할지 설정 , Armor는 "캡처할 대상 Attribute 이름"이고,반드시 UAuraAttributeSet 클래스에 존재해야 해요!
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics() {
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set by Caller Magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);
	// lec 144 - test용, Armor로 . 값 잘 들어간거 확인.
	//float Armor = 0.f;
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, Armor);
	//Armor = FMath::Max<float>(0.f, Armor);
	//++Armor;

	float BlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, BlockChance);
	BlockChance = FMath::Clamp<float>(BlockChance, 0.f, 100.f); // BlockChance는 0~100 사이로 제한
	float RandomValue = FMath::FRand() * 100.f; // 0~100 사이의 랜덤값 생성
	if (RandomValue < BlockChance) // BlockChance가 0보다 크고, 랜덤값이 BlockChance보다 작으면
	{
		// Blocked
		UE_LOG(LogTemp, Warning, TEXT("Damage blocked by %s!"), *TargetAvatar->GetName());
		Damage /= 2.f; // Blocked Damage는 절반으로 감소
	}


	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
