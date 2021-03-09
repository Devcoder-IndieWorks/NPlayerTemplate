// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include <GameFramework/Actor.h>
#include "NPlayerWarpMonitor.generated.h"

UCLASS( Blueprintable, BlueprintType )
class ANPlayerWarpMonitor : public AActor
{
    GENERATED_UCLASS_BODY()
public:
    virtual void Setup();

protected:
    void BeginPlay() override;

    UFUNCTION( BlueprintImplementableEvent, Category="NPlayerWarpMonitor|EVents" )
    void OnSetupLEDWarpWhenBeginPlay();

protected:
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="ScreenWarp" )
    bool EnableSetupWhenBeginPlay;
};
