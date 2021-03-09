// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include <GameFramework/Pawn.h>
#include "NPlayerStagePawn.generated.h"

UCLASS( Blueprintable, BlueprintType )
class ANPlayerStagePawn : public APawn
{
    GENERATED_UCLASS_BODY()
public:
    virtual class UPawnMovementComponent* GetMovementComponent() const override;
    virtual void SetupPlayerInputComponent( UInputComponent* InInputComponent ) override;
    virtual void Tick( float InDeltaSeconds ) override;

    //-------------------------------------------------------------------------

    UFUNCTION( BlueprintCallable, Category="NPlayerStagePawn" )
    virtual void MoveForward( float InValue );
    UFUNCTION( BlueprintCallable, Category="NPlayerStagePawn" )
    virtual void MoveRight( float InValue );
    UFUNCTION( BlueprintCallable, Category="NPlayerStagePawn" )
    virtual void MoveUpWorld( float InValue );

    UFUNCTION( BlueprintCallable, Category="NPlayerStagePawn" )
    virtual void TurnAtRate( float InRate );
    UFUNCTION( BlueprintCallable, Category="NPlayerStagePawn" )
    virtual void LookupAtRate( float InRate );

    //-------------------------------------------------------------------------

    UFUNCTION( BlueprintCallable, Category="NPlayerStagePawn" )
    void SendClusterEvent( const FString& InName, const FString& InType, const FString& InCategory, const TMap<FString, FString>& InParameters );

private:
    bool MoveInput( EAxis::Type InAxis, float InValue );
    bool MoveInnerFrustumCamera( EAxis::Type InAxis, float InValue );
    void RotateYawFrustumCamera( float InValue );
    void RotatePitchFrustumCamera( float InValue );

    UFUNCTION()
    void ChangeFocusDistance( float InValue );

protected:
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="NPlayerStagePawn|ControlInput" )
    float BaseTurnRate;
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="NPlayerStagePawn|ControlInput" )
    float BaseLookupRate;

    UPROPERTY( BlueprintReadWrite, Category="NPlayerStagePawn|ControlInput" )
    uint32 ControlInnerFrustumCamera:1;
    UPROPERTY( BlueprintReadWrite, Category="NPlayerStagePawn|ControlInput" )
    uint32 EnableControlInput:1;

private:
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="NPlayerStagePawn|ControlInput", meta=(AllowPrivateAccess="true") )
    uint32 AddDefaultMovementBindings:1;

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="NPlayerStagePawn|Components", meta=(AllowPrivateAccess="true") )
    class USceneComponent* OriginComponent;
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="NPlayerStagePawn|Components", meta=(AllowPrivateAccess="true") )
    class UPawnMovementComponent* MovementComponent;
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="NPlayerStagePawn|Components", meta=(AllowPrivateAccess="true") )
    class UCameraComponent* StageCameraComponent;

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="NPlayerStagePawn|InCamera", meta=(AllowPrivateAccess="true") )
    class ACineCameraActor* InnerFrustumCamera;

    //-------------------------------------------------------------------------

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="NPlayerStagePawn|ScreenWarp", meta=(AllowPrivateAccess="true") )
    class ANPlayerWarpMonitor* LEDWarpMonitor;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="NPlayerStagePawn|ScreenWarp", meta=(AllowPrivateAccess="true") )
    class ANPlayerStageReflectionViewPoint* StageReflectionViewPoint;

    //-------------------------------------------------------------------------

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="NPlayerStagePawn|nDisplayEvent", meta=(AllowPrivateAccess="true") )
    class ANPlayerEmitsClusterEvent* EmitsClusterEvent;
};
