// Copyright JackK


#include "Character/AuraCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include <Player/AuraPlayerController.h>
#include <UI/HUD/AuraHUD.h>


AAuraCharacter::AAuraCharacter()
{
 /*   CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraArm->SetupAttachment(GetCapsuleComponent());
    CameraArm->TargetArmLength = 750.f;
    CameraArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
    CameraArm->bEnableCameraLag = true;
    CameraArm->bInheritYaw = false;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);*/

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    CharacterClass = ECharacterClass::Elementalist;

}

void AAuraCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // Init ability actor info for the Server
    InitAbilityActorInfo();
    //lec 98
    AddCharacterAbilities();
}

void AAuraCharacter::InitAbilityActorInfo()
{
    AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
    Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
    // 지금 lec54하다가 보는중인데 아래 두개가 지금 이 클래스가 avataractor 라서 PlayerState에서 가져와서 씌운듯.
    AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
    AttributeSet = AuraPlayerState->GetAttributeSet();

    if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
    {
        if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
        {
            AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
        }
    }
    InitializeDefaultAttributes();
}

void AAuraCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    // Init ability actor info for the Client
    InitAbilityActorInfo();
}

int32 AAuraCharacter::GetPlayerLevel()
{
    const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->GetPlayerLevel();
}



void AAuraCharacter::BeginPlay()
{
    Super::BeginPlay();
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

}
