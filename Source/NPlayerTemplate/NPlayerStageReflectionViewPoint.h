// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include <GameFramework/Actor.h>
#include "NPlayerStageReflectionViewPoint.generated.h"

UCLASS( Blueprintable, BlueprintType )
class ANPlayerStageReflectionViewPoint : public AActor
{
    GENERATED_UCLASS_BODY()
public:
    virtual void Tick( float InDeltaSeconds ) override;
    virtual void UpdateStageReflectionViewPoint();

protected:
    UFUNCTION( BlueprintImplementableEvent, Category="NPlayerStageReflectionViewPoint|EVents" )
    void OnLEDStageReflectionViewPoint();

private:
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="NPlayerStageReflectionViewPoint|Tick", meta=(AllowPrivateAccess="true") )
    uint32 EnableTickUpdateStageReflectionViewPoint:1;
};
