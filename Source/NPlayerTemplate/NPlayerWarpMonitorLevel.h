// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "NPlayerWarpMonitor.h"
#include "NPlayerWarpMonitorLevel.generated.h"

UCLASS() 
class ANPlayerWarpMonitorLevel : public ANPlayerWarpMonitor
{
    GENERATED_UCLASS_BODY()
public:
    virtual void Setup() override;

protected:
    UFUNCTION( BlueprintImplementableEvent, Category="NPlayerWarpMonitorLevel|EVents" )
    void OnLEDWarpMappings( const FString& InViewportId, class UStaticMeshComponent* InMeshComponent );

private:
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="ScreenWarp", meta=(AllowPrivateAccess="true") )
    TMap<FString, class AStaticMeshActor*> LEDWarpMappings;

    //-------------------------------------------------------------------------

    bool IsSetupLEDWarps;
};
