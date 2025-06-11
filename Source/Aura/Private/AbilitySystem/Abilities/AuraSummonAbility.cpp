// Copyright JackK


#include "AbilitySystem/Abilities/AuraSummonAbility.h"
#include <Kismet/KismetSystemLibrary.h>

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);

	TArray<FVector> SpawnLocations;

	for (int32 i = 0; i < NumMinions; i++) {
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		const FVector SpawnLocation = Location + Direction * FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawnLocations.Add(SpawnLocation);


	}

	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + LeftOfSpread * MaxSpawnDistance, 4.f, FLinearColor::Green, 3.f);

	DrawDebugSphere(GetWorld(), Location+LeftOfSpread * MinSpawnDistance, 15.f, 12, FColor::Red, false, 3.f);
	DrawDebugSphere(GetWorld(), Location + LeftOfSpread * MaxSpawnDistance, 15.f, 12, FColor::Red, false, 3.f);

	const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpread / 2.f, FVector::UpVector);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + RightOfSpread * MaxSpawnDistance, 4.f, FLinearColor::Gray, 3.f);

	DrawDebugSphere(GetWorld(), Location + RightOfSpread * MinSpawnDistance, 15.f, 12, FColor::Red, false, 3.f);
	DrawDebugSphere(GetWorld(), Location + RightOfSpread * MaxSpawnDistance, 15.f, 12, FColor::Red, false, 3.f);

	return TArray<FVector>();
}
