#include "NPlayerWarpMonitor.h"

ANPlayerWarpMonitor::ANPlayerWarpMonitor( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    EnableSetupWhenBeginPlay = true;
}

void ANPlayerWarpMonitor::BeginPlay()
{
    if ( EnableSetupWhenBeginPlay )
        OnSetupLEDWarpWhenBeginPlay();

    Super::BeginPlay();
}

void ANPlayerWarpMonitor::Setup()
{
}
