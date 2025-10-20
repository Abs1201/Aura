// Copyright JackK


#include "AbilitySystem/Abilities/AuraBeamSpell.h"
#include "GameFramework/Character.h"
#include <Kismet/KismetSystemLibrary.h>
#include <AbilitySystem/AuraAbilitySystemLibrary.h>

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if (HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	if (CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerCharacter);
	if(OwnerCharacter->Implements<UCombatInterface>())
	{
		if(USkeletalMeshComponent* WeaponMesh = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(OwnerCharacter);
			FHitResult HitResult;
			const FVector SocketLocation = WeaponMesh->GetSocketLocation(FName("TipSocket"));
			UKismetSystemLibrary::SphereTraceSingle(OwnerCharacter, SocketLocation, BeamTargetLocation, 10.f, 
				TraceTypeQuery1, false, ActorsToIgnore, 
				EDrawDebugTrace::None, /*out*/ HitResult, true);

			if (HitResult.bBlockingHit)
			{
				MouseHitLocation = HitResult.ImpactPoint;
				MouseHitActor = HitResult.GetActor();
			}
		}
	}
	//333
	if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(MouseHitActor))
	{
		if (!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::PrimaryTargetDied))
		{
			CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::PrimaryTargetDied);
		}
	}
}
// 329
void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	ActorsToIgnore.Add(MouseHitActor);

	TArray<AActor*> OverlappingActors;

	UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(
		GetAvatarActorFromActorInfo(),
		OverlappingActors,
		ActorsToIgnore,
		850.f, // 전기 연쇄 공격 범위.
		MouseHitActor->GetActorLocation());
	int32 NumAdditionalTargets = FMath::Min(GetAbilityLevel()-1, MaxNumShockTargets);
	//int32 NumAdditionTargets = 5;
	UAuraAbilitySystemLibrary::GetClosestTargets(NumAdditionTargets, OverlappingActors, OutAdditionalTargets, MouseHitActor->GetActorLocation());
	
	for (AActor* Target : OutAdditionalTargets)
	{
		if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(Target))
		{
			if (!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::AdditionalTargetDied))
			{
				CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::AdditionalTargetDied);
			}
		}
	}

}
