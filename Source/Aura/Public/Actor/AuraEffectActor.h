// Copyright JackK

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"

#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotApply
};


UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	//423 Loot Effect
	UPROPERTY(BlueprintReadOnly)
	FVector CalculatedLocation;

	UPROPERTY(BlueprintReadOnly)
	FRotator CalculatedRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	bool bRotates = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float RotationRate = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	bool bSinusoidalMovement = false;

	UFUNCTION(BlueprintCallable)
	void StartSinusoidalMovement();

	UFUNCTION(BlueprintCallable)
	void StartRotation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float SineAmplitude = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float SinePeriodConstant = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	FVector InitialLocation;


	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	// diff in lec 27
	// start in lec 43
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	bool bDestroyOnEffectApplication = false;
	//lec 168
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	bool bApplyEffectsToEnemies = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = "Applied Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect") 
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	// only needs in infinite effect cuz others will destroy itself after duration or instantly.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied Effect")
	float ActorLevel=1.f;

private:
	//423 Loot Effect
	float RunningTime = 0.f;
	void ItemMovement(float DeltaTime);
};
