// Copyright JackK


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

//#include "DrawDebugHelpers.h"


AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 20.f, 20, FColor::Blue, false, 5.f);
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);


}

void AAuraEnemy::UnHighlightActor()
{
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 20.f, 20, FColor::Red, false, 5.f);
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);


}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);



}
