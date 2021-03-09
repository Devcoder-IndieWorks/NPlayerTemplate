// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include <GameFramework/Actor.h>
#include "NPlayerEmitsClusterEvent.generated.h"

UCLASS( Blueprintable, BlueprintType ) 
class ANPlayerEmitsClusterEvent : public AActor
{
    GENERATED_UCLASS_BODY()
public:
    UFUNCTION( BlueprintImplementableEvent, Category="NPlayerEmitsClusterEvent|Events" )
    void SendClusterEvent( const FString& InName, const FString& InType, const FString& InCategory, const TMap<FString, FString>& InParameters );
};
