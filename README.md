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

* ### NPlayer Template Project 설정

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

      ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShot/ChromakeyLayer_Sample.png)

      NPlayer Template에서는 Green색으로 지정된 Plane인 GreenScreenPlane Actor를 추가하여  설정.

  * DisplayClusterRootActor: 이 Actor의 위치는 외부 Frustum이 투영되는 원근을 정의 한다. 만일 BP_NPlayerStageReflectionViewPoint Actor를 배치 했다면, 외부 Frustum이 투영되는 원근 정의는 BP_NPlayerStageReflectionViewPoint Actor 위치를 기반으로 정의 된다.

    ![](https://github.com/Devcoder-Indieworks/NPlayerTemplate/blob/master/ScreenShots/DisplayClusterRootActor_Detail.png)

    Show projection screens 항목을 check 해 주고, 옵션으로 Projection screen material를 설정 해 줄 수도 있다.

