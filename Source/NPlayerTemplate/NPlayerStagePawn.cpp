#include "NPlayerStagePawn.h"
#include "NPlayerWarpMonitor.h"
#include "NPlayerStageReflectionViewPoint.h"
#include "NPlayerEmitsClusterEvent.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SceneComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/PawnMovementComponent.h>
#include <GameFramework/FloatingPawnMovement.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerInput.h>
#include <Engine/CollisionProfile.h>
#include <Engine/StaticMesh.h>
#include <Engine/StaticMeshActor.h>
#include <UObject/ConstructorHelpers.h>
#include <CineCameraActor.h>
#include <CineCameraComponent.h>

void __InitializeDefaultInputBindings()
{
    static bool bindingsAdded = false;
    if ( !bindingsAdded ) {
        bindingsAdded = true;

        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveForward" ), EKeys::W,     1.0f ) );
        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveForward" ), EKeys::S,    -1.0f ) );
        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveForward" ), EKeys::Up,    1.0f ) );
        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveForward" ), EKeys::Down, -1.0f ) );

        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveRight" ), EKeys::A,    -1.0f ) );
        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveRight" ), EKeys::D,     1.0f ) );
        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveRight" ), EKeys::Left, -1.0f ) );
        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveRight" ), EKeys::Right, 1.0f ) );

        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveUp" ), EKeys::SpaceBar, 1.0f ) );
        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveUp" ), EKeys::E,  1.0f ) );
        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_MoveUp" ), EKeys::C, -1.0f ) );

        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_TurnRate" ), EKeys::MouseX,    1.0f ) );
        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_LookUpRate" ), EKeys::MouseY, -1.0f ) );

        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_FocusDistance" ), EKeys::Home, 1.0f ) );
        UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( TEXT( "StagePawn_FocusDistance" ), EKeys::End, -1.0f ) );
    }
}

ANPlayerStagePawn::ANPlayerStagePawn( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    SetRemoteRoleForBackwardsCompat( ROLE_SimulatedProxy );
    bReplicates = true;
    NetPriority = 3.0f;

    BaseEyeHeight = 0.0f;
    bCollideWhenPlacing = false;
    SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // Create roo scene component.
    OriginComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "MainRoot" ) );
    RootComponent = OriginComponent;

    // Create pawn movement component.
    MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>( TEXT( "StageMovement" ) );
    MovementComponent->UpdatedComponent = OriginComponent;

    // Create camera component.
    StageCameraComponent = CreateDefaultSubobject<UCameraComponent>( TEXT( "StageCamera" ) );
    StageCameraComponent->SetupAttachment( OriginComponent );
    StageCameraComponent->bUsePawnControlRotation = true;

    ControlInnerFrustumCamera = false;
    EnableControlInput = true;
    AddDefaultMovementBindings = true;

    BaseTurnRate = 45.0f;
    BaseLookupRate = 45.0f;
}

void ANPlayerStagePawn::SetupPlayerInputComponent( UInputComponent* InPlayerInputComponent )
{
    if ( ensure( InPlayerInputComponent != nullptr ) ) {
        if ( AddDefaultMovementBindings ) {
            __InitializeDefaultInputBindings();

            InPlayerInputComponent->BindAxis( TEXT( "StagePawn_MoveForward" ), this, &ANPlayerStagePawn::MoveForward );
            InPlayerInputComponent->BindAxis( TEXT( "StagePawn_MoveRight" ), this, &ANPlayerStagePawn::MoveRight );
            InPlayerInputComponent->BindAxis( TEXT( "StagePawn_MoveUp" ), this, &ANPlayerStagePawn::MoveUpWorld );
            InPlayerInputComponent->BindAxis( TEXT( "StagePawn_TurnRate" ), this, &ANPlayerStagePawn::TurnAtRate );
            InPlayerInputComponent->BindAxis( TEXT( "StagePawn_LookUpRate" ), this, &ANPlayerStagePawn::LookupAtRate );

            InPlayerInputComponent->BindAxis( TEXT( "StagePawn_FocusDistance" ), this, &ANPlayerStagePawn::ChangeFocusDistance );
        }
    }
}

void ANPlayerStagePawn::MoveForward( float InValue )
{
    if ( EnableControlInput )
        auto ret = ControlInnerFrustumCamera ? MoveInnerFrustumCamera( EAxis::X, InValue ) : MoveInput( EAxis::X, InValue );
}

void ANPlayerStagePawn::MoveRight( float InValue )
{
    if ( EnableControlInput  )
        auto ret = ControlInnerFrustumCamera ? MoveInnerFrustumCamera( EAxis::Y, InValue ) : MoveInput( EAxis::Y, InValue );
}

bool ANPlayerStagePawn::MoveInnerFrustumCamera( EAxis::Type InAxis, float InValue )
{
    if ( InValue != 0.0f ) {
        if ( ensure( InnerFrustumCamera != nullptr ) ) {
            auto location = InnerFrustumCamera->GetActorLocation();
            auto const rotation = InnerFrustumCamera->GetActorRotation();
            auto dir = FRotationMatrix(rotation).GetScaledAxis( InAxis );
            const float MOVE_SPEED = 100.0f;
            auto newLocation = location + (dir * MOVE_SPEED * InValue * GetWorld()->GetDeltaSeconds() * CustomTimeDilation );
            InnerFrustumCamera->SetActorLocation( newLocation );
            return true;
        }
    }
    return false;
}

bool ANPlayerStagePawn::MoveInput( EAxis::Type InAxis, float InValue )
{
    if ( InValue != 0.0f ) {
        if ( ensure( Controller != nullptr ) ) {
            auto const controlSpaceRot = Controller->GetControlRotation();
            AddMovementInput( FRotationMatrix(controlSpaceRot).GetScaledAxis( InAxis ), InValue );
            return true;
        }
    }
    return false;
}

void ANPlayerStagePawn::MoveUpWorld( float InValue )
{
    if ( EnableControlInput && InValue != 0.0f )
        AddMovementInput( FVector::UpVector, InValue );
}

void ANPlayerStagePawn::TurnAtRate( float InRate )
{
    if ( EnableControlInput ) {
        float value = InRate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation;
        if ( ControlInnerFrustumCamera )
            RotateYawFrustumCamera( value );
        else
            AddControllerYawInput( value );
    }
}

void ANPlayerStagePawn::RotateYawFrustumCamera( float InValue )
{
    if ( ensure( InnerFrustumCamera != nullptr ) ) {
        auto rotation = InnerFrustumCamera->GetActorRotation();
        rotation.Yaw += InValue;
        InnerFrustumCamera->SetActorRotation( rotation );
    }
}

void ANPlayerStagePawn::LookupAtRate( float InRate )
{
    if ( EnableControlInput ) {
        float value = InRate * BaseLookupRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation;
        if ( ControlInnerFrustumCamera )
            RotatePitchFrustumCamera( value );
        else
            AddControllerPitchInput( value );
    }
}

void ANPlayerStagePawn::RotatePitchFrustumCamera( float InValue )
{
    if ( ensure( InnerFrustumCamera != nullptr ) ) {
        auto rotation = InnerFrustumCamera->GetActorRotation();
        rotation.Pitch += InValue;
        InnerFrustumCamera->SetActorRotation( rotation );
    }
}

void ANPlayerStagePawn::ChangeFocusDistance( float InValue )
{
    if ( ensure( InnerFrustumCamera != nullptr ) ) {
        float value = InValue * 200.0f * GetWorld()->GetDeltaSeconds() * CustomTimeDilation;
        InnerFrustumCamera->GetCineCameraComponent()->FocusSettings.ManualFocusDistance += value;
        //UE_LOG(LogTemp, Log, TEXT( "#### Cine camera component menual focus distance: [%f] ####" ), InnerFrustumCamera->GetCineCameraComponent()->FocusSettings.ManualFocusDistance );
    }
}

UPawnMovementComponent* ANPlayerStagePawn::GetMovementComponent() const
{
    return MovementComponent;
}

void ANPlayerStagePawn::Tick( float InDeltaSeconds )
{
    if ( LEDWarpMonitor != nullptr )
        LEDWarpMonitor->Setup();

    if ( StageReflectionViewPoint != nullptr )
        StageReflectionViewPoint->UpdateStageReflectionViewPoint();

    Super::Tick( InDeltaSeconds );
}

void ANPlayerStagePawn::SendClusterEvent(  const FString& InName, const FString& InType, const FString& InCategory, const TMap<FString, FString>& InParameters  )
{
    if ( ensure( EmitsClusterEvent != nullptr ) )
        EmitsClusterEvent->SendClusterEvent( InName, InType, InCategory, InParameters );
}
