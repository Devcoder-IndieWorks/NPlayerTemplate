# nDisplay Rendering Pipeline에 Motion Blur 기능 추가

----------------------------------------------------------------------------------------------------------------------------------------------------------------

### 개요

nDisplay는 하나의 씬을 여러 화면/디바이스(PC)에 나누어서 렌더링하여 각 화면/디바이스(PC)에 출력해 주는 기능을 제공한다. 이렇게 여러 화면에 나누어 렌더링하다 보니 화면/디바이스(PC)간 갱신 주기가 맞지 않아 **Screen Tearing** 현상이 발생하게 된다.

특히 Screen Space 기반 Post-Process 결과물은 더욱 더 Screen Tearing 현상이 두더러지게 나타나는데, 그래서 nDisplay에서는 Post-Process 기능 사용을 권장하지 않는다. 

하지만, 여러 디바이스(PC)에 나누어서 렌더링하지 않고, 하나의 디바이스(PC)에서만 렌더링하여 다중 디스플레이로 출력하고, In Camera VFX 기능을 사용할 때 Screen Space 기반 Post-Process 효과 중 하나인 Motion Blur 기능을 작동 시키면 Motion Blur 기능이 정상 작동 하지 않는다.**(최종확인 UE4 4.26.1에서)**

그래서 Screen Tearing 현상이 잘 발생하지 않는 nDisplay 구성에서 In Camera VFX 기능을 이용하고자 하는 프로젝트에서 Motion Blur 기능을 활성화 하고자 할 때 Motion Blur 기능이 작동 하도록 하기  위해 UE4 엔진 코드를 수정하는 방법을 설명하고자 한다.

----------------------------------------------------------------------------------------------------------------------------------------------------------------

### Motion Blur 기능이 활성화 되도록 엔진 코드 수정

nDisplay에서 Motion Blur가 작동하지 않는 원인은 nDisplay는 UE4의 StereoRenderingDevice 인터페이스를 활용하여 Unreal Rendering System과 연동 되어 있고, UE4에서는 StereoRenderingDevice로 렌더링을 하게 되면 Motion Blur 기능이 작동되지 않도록 되어져 있다.

다음 코드가 StereoRenderingDevice 인터페이스에 DisplayClusterRenderDevice를 설정하는 코드이다.

![](https://github.com/Devcoder-IndieWorks/NPlayerTemplate/blob/master/ScreenShots/DisplayClusterRenderManager.png)

nDisplay Plugin의 DisplayClusterRenderManager.cpp 파일에 정의 되어 있으며, UE4 PostProcess 단계에서 StereoRenderingDevice 인터페이스 참조가 유효하면 PostProcess 단계에 Motion Blur Pass를 추가 하지 않는다.

![](https://github.com/Devcoder-IndieWorks/NPlayerTemplate/blob/master/ScreenShots/PostProcessMotionBlur.png)

**빨간색 박스 영역**이 **GEngine->StereoRenderingDevice 유효성 검사** 및 **Stereo Rendering 활성화 여부를 체크**하는 부분이다.(**참고로 노란색 박스 영역은 nDisplay에서 Motion Blur 효과 사용 유무를 선택 할 수 있게 추가된 부분이다.**)

위 코드가 true이면 PostProcess 단계에 Motion Blur Pass가 추가 되나, 그렇지 않다면 Motion Blur Pass가 추가 되지 않는다.

![](https://github.com/Devcoder-IndieWorks/NPlayerTemplate/blob/master/ScreenShots/PostProcessing.png)

그래서 nDisplay 실행시 Motion Blur Pass를 PostProcess 단계에 추가하기 위해 UE4 엔진 코드에 몇가지 코드를 추가 하였다.

우선 nDisplay 실행 중 Motion Blur 사용 유무를 설정 할 수 있는 옵션 설정 항목을 PostProcessMotionBlur.cpp에 추가 하였다.

![](https://github.com/Devcoder-IndieWorks/NPlayerTemplate/blob/master/ScreenShots/Add_Console_Variable_Motion_Blur.png)

PostProcessMotionBlur.cpp 파일에 TAutoCosoleVariable<int32> 항목을 추가하고, 이 항목 값을 통해 Motion Blur Pass를 추가 할지 결정 되도록 PostProcessMotionBlur.cpp 파일의 bool IsMotionBlurEnabled() 함수에 Console Variable 코드를 추가 했다.

그리고, 프로젝트 설정에서 CVarAllowMotionBlurInNDisplay 항목을 설정 할 수 있게 RenderSettings.h 파일에 프로젝트 설정 항목도 추가 한다.

![](https://github.com/Devcoder-IndieWorks/NPlayerTemplate/blob/master/ScreenShots/RenderSettings.png)

RenderSettings.h에 항목을 추가하게 되면 프로젝트 설정에서 다음과 같은 항목이 보이게 된다.

![](https://github.com/Devcoder-IndieWorks/NPlayerTemplate/blob/master/ScreenShots/MotionBlur_Project_Setting.png)

