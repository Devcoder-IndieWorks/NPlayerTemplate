#include "NPlayerWarpMonitorLevel.h"
#include <Components/StaticMeshComponent.h>
#include <Engine/StaticMesh.h>
#include <Engine/StaticMeshActor.h>

ANPlayerWarpMonitorLevel::ANPlayerWarpMonitorLevel( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    EnableSetupWhenBeginPlay = false;
    IsSetupLEDWarps = false;
}

void ANPlayerWarpMonitorLevel::Setup()
{
    if ( EnableSetupWhenBeginPlay )
        return;

    if ( !IsSetupLEDWarps ) {
        if ( LEDWarpMappings.Num() > 0 ) {
            IsSetupLEDWarps = true;

            for ( auto LEDWarp : LEDWarpMappings ) {
                if ( LEDWarp.Value == nullptr || LEDWarp.Value->GetStaticMeshComponent() == nullptr ) {
                    IsSetupLEDWarps = false;
                    break;
                }

                OnLEDWarpMappings( LEDWarp.Key, LEDWarp.Value->GetStaticMeshComponent() );
            }
        }
    }
}
