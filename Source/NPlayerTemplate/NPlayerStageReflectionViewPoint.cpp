#include "NPlayerStageReflectionViewPoint.h"

ANPlayerStageReflectionViewPoint::ANPlayerStageReflectionViewPoint( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
    EnableTickUpdateStageReflectionViewPoint = true;
}

void ANPlayerStageReflectionViewPoint::Tick( float InDeltaSeconds )
{
    if ( EnableTickUpdateStageReflectionViewPoint )
        OnLEDStageReflectionViewPoint();

    Super::Tick( InDeltaSeconds );
}

void ANPlayerStageReflectionViewPoint::UpdateStageReflectionViewPoint()
{
    if ( !EnableTickUpdateStageReflectionViewPoint )
        OnLEDStageReflectionViewPoint();
}