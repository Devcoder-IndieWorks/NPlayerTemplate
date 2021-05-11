# nDisplay Rendering Pipeline에 NVIDIA DLSS 기능 추가

----------------------------------------------------------------------------------------------------------------------------------------------------------------

### UE4에서 NVIDIA DLSS 활성화 하기

* DLSS Plugin을 프로젝트에서 사용 가능하도록 Engine의 Plugin 폴더에 추가 한다.

* 프로젝트의 DefaultEngine.ini 파일에서 DLSS 환경설정 항목을 추가 한다.

  <pre>
      <code>
      [/Script/DLSS.DLSSSettings]
      bEnableDLSSInEditorViewports=True
      bEnableDLSSInPlayInEditorViewports=True
      bEnableNonProductionBinariesInShipping=True
      NVIDIANGXApplicationId=0
      </code>
  </pre>

* NVIDIANGXApplicationId는 NVIDIA DLSS Developer Network에서 발급 받은 Application ID를 입력해 준다.

* nDisplay에서 DLSS 활성화를 위해서는 추가적인 환경설정 항목을 하나 더 추가 한다.

  <pre>
      <code>
      [/Script/Engine.RendererSettings]
      r.TemporalAA.Upsampling=True
      </code>
  </pre>

* nDisplay에서는 r.TemporalAA.Upsampling 기본값이 False로 되어져 있다.(확실하게 꼭 그렇다라기보다는 DLSS 기능이 Upsampling 기능을 이용하므로 확실하게 설정 해 두는것이 좋은 방법이라 생각 됨.)

----------------------------------------------------------------------------------------------------------------------------------------------------------------

### NVIDIA DLSS 사용하기 위한 UE4 Engine Code 수정 하기

NVIDIA DLSS 사용하기 위한 설정을 해도 nDisplay 실행시 DLSS 기능이 작동하지 않는다. 그 이유는 PostProcessing.cpp 파일에 있는 AddPostProcessingPass() 함수 내용 중 Line 511 ~ 523 부분이 다음 코드에 이유가 있다.

![](https://github.com/Devcoder-IndieWorks/NPlayerTemplate/blob/master/ScreenShots/AddPostProcessingPass.png)

윗쪽 빨간색박스의 내용인 **GetTemporalUpscalerInterface()가 nullptr 값을 반환**하여 아랫쪽 빨간색박스의 내용인 **UpscalerToUse != DefaultTemporalUpscaler가 false**가 되어 **Third Party Upscaler**가 등록되지 않아 DLSS 기능이 작동하지 않는것이다.

**View.Family->GetTemporalUpscalerInterface()**에 유효한 인스턴스가 존재해야 하는데, ViewFamily에 TemporalUpscaler를 설정 하는 코드가 nDisplay 관련 코드에 존재 하지 않는다.

그래서 nDisplay 실행시 사용되는 **UDisplayClusterViewportClient::Draw()**함수 내 다음 구현 내용들을 추가항여 ViewFamily에 DLSS Upscaler 인스턴스가 설정 되도록 해 준다.

![](https://github.com/Devcoder-IndieWorks/NPlayerTemplate/blob/master/ScreenShots/modify_dlss_ue4_1.png)

**GCustomStaticScreenPercentage** 를 사용하기 위해 헤더파일을 Include 해 준다.

![](https://github.com/Devcoder-IndieWorks/NPlayerTemplate/blob/master/ScreenShots/modify_dlss_ue4_2.png)

Line 497 ~ 498 부분에 **GCustomStaticScreenPercentage->SetupMainGameViewFamily()**를 호출하여 Game View Family를 통해 DLSS Upscaler 인스턴스가 사용 될 수 있도록 해 준다.

