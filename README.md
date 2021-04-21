# NPlayer Template

--------------------------------------------------------------------------------------------------------------------------------------------------------------

UE4 In Camera VFX Template Project가 C++ Project를 지원하지 않아, C++로 UE4 In Camera VFX Project를 시작 할 수 있도록 하기 위한 Template Project.

---------------------------------------------------------------------------------------------------------------------------------------------------------------

* ### UE4 In Camera VFX에 필요한 Plugins

  * #### 필수 항목

    * nDisplay: 다중 디스플레이 렌더링 지원.
    * VirtualProductionUtilities: Virtual Production 제작시 유용하게 사용할 수 있는 유틸리티 기능을 제공.
    * MediaFrameworkUtilities: SDI 캡처 카드의 라이브 비디오, 타임 코드 및 젠록과 관련된 유틸리티 기능을 제공.
    * AjaMedia: Aja SDI 캡처 카드를 지원.
    * BlackmagicMedia: Blackmagic SDI 캡처 카드를 지원.
    * MultiUserClient: UE4에서 여러 편집자가 공유 세션에 참가하여 같이 편집 하는 기능 제공.
    * LiveLink: UE4에서 모션 캡처 및 카메라 Tracking과 같은 라이브 데이터를 수집하기 위한 기능 제공.
    * LiveLinkOverNDisplay: Primary 노드는 LiveLink 데이터를 수신하고, 효율적으로 동기화 되도록 수신된 데이터를 재분배 하기 위한 기능 제공.

  * #### 옵션 항목

    * SequencerScripting
    * OSC
    * RemoteControl

----------------------------------------------------------------------------------------------------------------------------------------------------------------

* ### NPlayer Template Project  설정

  NPlayer Template는 UE4 In Camera VFX Template Project와 다른점은 NPlayer Template 전용 Pawn 엑터를 구현하여 입력 처리를 Customization 할 수 있다는 점이다.

  전용 Pawn 엑터는 C++로 구현되어져 있어 C++ API 를 이용하여 Pawn에 여러가지 기능을 통합 할 수 있다.

  * NPlayer Template Stage Hierarchy

    ![](https://github.com/Devcoder-IndieWorks/NPlayerTemplate/blob/master/ScreenShots/NPlayerTemplateStageHierarchy.png)

  * BP_NPlayerStageOrigin Actor: Stage Hierarchy의 Root 역할을 하며, Root를 이동하면 하위에 존재하는 Actors 모두가 월드상에서 동일한 위치를 유지하며 이동 시킬 수 있다.

  * BP_IncameraSettings Actor: UE4 nDisplay에서 제공하는 Actor로써, 내부용 Frustum Camera를 설정 한다. 이 Frustum Camera는 Detail 패널의 Default 항목에 있는 Reprojected Cine Camera 속성에서 지정하면 된다. 그리고 Frustum Camera의 Edge Blending 영역과 Camera 프레임 섹션에 있는 FOV 승수값을 설정 할 수 있다.

    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/BP_IncameraSettings_Detail.png)

    * RTTViewportID: nDisplay Config 파일에서 설정한 [viewport] id="XXXXX" projection="proj_incamera" 항목 중 id에 설정한 내용을 입력해 준다.
    * Inner Camera Soft Edge: 내부용 Frustom Camera의 외곽을 Bluring 할 영역 크기를 지정(X,Y,Z 전부 0이면 Soft Edge 비활성화)
    * FOVMultiplier: FOV 승수 값 지정.

  * BP_IncameraStageSettings Actor: UE4 nDisplay에서 제공하는 Actor로써, 크로마키 마커를 설정 할 수 있다. Detail 패널의 Chromakey 카테고리에서 Chromakey Marker 항목에 Chromakey 텍스쳐 어셋을 설정 할 수 있다.

    렌더링 카테고리에서 LED에 표시 되지 않을 Actor들을 설정 할 Hidden Layers 배열을 추가 할 수 있고, Light Cards 카테고리에 Light Card 역할을 할 Actor들을 설정 할 Light Cards Layer 추가 할 수 있다. Light Cards는 LED Stage에 조명을 제공하기 위함으로 외부 Frustum에서만 볼 수 있다.

    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/BP_IncameraStageSettings_Detail.png)

    * Enabled: Chromakey 활성화 여부 설정.
    * Chromakey Layer: Chromakey 영역으로 캡처할 Actor들이 나열된 Layer들을 등록.
    * Chromakey Marker: Chromakey 영역에 표시 될 Chromakey 텍스쳐 어셋 설정.
    * Chromakey Marker Scale: Chromakey 영역에 표시 될 마크 크기 지정.
    * Chromakey Marker UV Source: Chromakey 영역에 표시 될 마크 UV 방식 지정.
    * 옵션으로 지정 할 설정
      * Hidden Layers: Hidden Layer들 설정.
      * Light Cards Layer: Light Cards Layer 설정.

    * Chromakey Layer 샘플

      ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/ChromakeyLayer_Sample.png)

      NPlayer Template에서는 Green색으로 지정된 Plane인 GreenScreenPlane Actor를 추가하여  설정.

  * DisplayClusterRootActor: 이 Actor의 위치는 외부 Frustum이 투영되는 원근을 정의 한다. 만일 BP_NPlayerStageReflectionViewPoint Actor를 배치 했다면, 외부 Frustum이 투영되는 원근 정의는 BP_NPlayerStageReflectionViewPoint Actor 위치를 기반으로 정의 된다.

    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/DisplayClusterRootActor_Detail.png)

    Show projection screens 항목을 check 해 주고, 옵션으로 Projection screen material를 설정 해 줄 수도 있다.

  * InnerFrustum (Cine Camera Actor): 실제 촬영하는 카메라의 Tracking 정보를 입력 받아 내부용 Frustum 투영 효과를 만드는 Camera Actor(실제 In Camera VFX 기능을 한다.)

    이 InnerFrustum 아래에 Chromakey 할 영역을 만들어 주는 GreenScreenPlane인 StaticMesh Actor를 놓아 둔다.

    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/InnerFrustum_Hierarchy.png)

  * BP_NPlayerStageReflectionViewPoint Actor: LED 화면에 투영하기 위한 카메라 위치를 설정하는 Actor.
  
    NPlayerTemplate에서는 NPlayerStagePawn에서 LED 화면 투영 카메라 위치를 업데이트 할 수 있도록 하기 위한 기능이 추가 되었다.
  
    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/BP_NPlayerStageReflectionViewPoint_Detail.png)
  
    Enable Tick Update Stage Reflection View Point를 check 하면 Tick 함수에서 카메라 위치를 업데이트하고, uncheck 하면 NPlayerStagePawn의 Tick 함수에서 카메라 위치를 업데이트 한다.
  
  * BP_NPlayerWarpMonitor / BP_NPlayerWarpMonitorLevel Actor: LED 화면에 투영할 카메라 Viewport 크기 및 영역을 설정 할 때 사용하는 Static Mesh를 nDisplay Picp Mesh Module에 등록하는 기능을 담당하는 Actor.
  
    BP_NPlayerWarpMonitor는 Static Mesh Component를 Actor 안에 직접 추가하여 BeginPlay 이벤트에서 nDisplay Picp Mesh Module에 등록하는 방식으로 동작한다.
  
    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/BP_NPlayerWarpMonitor.png)
  
    (Actor에 StatckMeshComponent를 추가한 모습)
  
    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/BP_NPlayerWarpMonitor_BeginPlayEvent.png)
  
    (OnSetupLEDWarpWhenBeginPlay 이벤트에서 Picp Mesh Module에 등록)
  
    BP_NPlayerWarpMonitorLevel은 World에 배치된 StaticMesh Actor들을 참조하여 실행시 nDisplay Picp Mesh Module에 등록하는 방식으로 동작한다.
  
    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/BP_NPlayerWarpMonitorLevel.png)
  
    (World에 배치된 StaticMesh Actor)
  
    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/BP_NPlayerWarpMonitorLevel_Detail.png)
  
    (LEDWarp Mappings 목록에 World에 배치된 StaticMesh Actor들을 등록)
  
    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/BP_NPlayerWarpMonitorLevel_BPEvent.png)
  
    (OnLEDWarpMappings 이벤트에서 Picp Mesh Module에 등록)
  
    **BP_NPlayerWarpMonitorLevel Actor를 World에 배치 할 때 주의 해야 할 점은 Actor 위치가 Warp Mesh(Group)의 중심을 바라보는 위치에 배치 해 줘야 한다. Warp Mesh(Group)의 중심을 바라 보는 위치가 아니라면, 실행시 Projection 되는 화면 영상이 틀어져 보이게 된다.**
  
  * BP_NPlayerStagePawn Actor: NPlayer Template 전용 Pawn Actor.
  
    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/BP_NPlayerStagePawn_Detail.png)
  
    * Inner Frustum Camera: World에 배치된 InnerFrustum Cine Camera Actor를 등록한다.
    * LEDWarp Monitor: World에 배치된 BP_NPlayerWarpMonitor Actor를 등록한다.
    * Stage Reflection View Point: World에 배치된 BP_NPlayerStageReflectionViewPoint Actor를 등록한다.

------------------------------------------------------------------------------------------------------------------------------------------------

* ### NPlayerStagePawn 사용

  * NPlayerStagePawn / InnerFrustum 조작

    UE4에서 기본 정의된 Key Bind로 이동이 가능하고, 마우스를 통해 Yaw, Pitch 회전이 가능하다. UE4에서 기본 정의된 Key Bind 대신 새로 Key Bind를 정의해서 사용 할 수도 있다.

    기본 설정 Key

    * W / S: 전후 이동
    * A / D: 좌우 이동
    * E / C: 위아래 이동
    * Mouse: Yaw, Pitch 회전

    NPlayerStagePawn의 ControlInput 항목에서 Add Default Movement Bindings를 체크 해재 하면 기본 Key Bind를 사용하지 않고, 새로 Key Bind를 정의 할 수 있다.

  * NPlayerStagePawn 입력 기능여부 설정

    실행 중 NPlayerStagePawn 이동과 회전 입력이 되지 않도록 할 수 있는데,  O Key를 누르면 된다. 다시 이동과 회전 입력이 되고자 한다면, 다시 O Key를 누르면 된다.

    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/NPlayerStagePawn_Input.png)

  * NPlayerStagePawn과 InnerFrustum 입력 전환

    기본 값으로 설정된 Key로 Pawn 뿐만 아니라, Inner Frustum 카메라 이동과 회전도 제어 가능하다. Inner Frustum 카메라 이동과 회전 입력을 사용 할 수 있도록 하기 위해서는 P Key를 누르면 된다. 다시 Pawn의 이동과 회전 입력을 하고자 한다면, 다시 P Key를 누르면 된다.

    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/InnerFrustumCamera_Input.png)

----------------------------------------------------------------------------------------------------------------------------------------------------------------

* ### NPlayer Template 실행

  nDisplay 기능이 정상 동작하기 위해서는 nDisplay 기능을 활성화 시켜줘야 한다. nDisplay 기능 활성화는 Project Settings의 nDisplay에서 Enable 항목을 check 해 주면 된다.

