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

    ![](D:\DevcoderWorks\WorksVirtualProduct\NPlayerTemplate\ScreenShots\NPlayerTemplateStageHierarchy.png)

  * BP_NPlayerStageOrigin Actor: Stage 

