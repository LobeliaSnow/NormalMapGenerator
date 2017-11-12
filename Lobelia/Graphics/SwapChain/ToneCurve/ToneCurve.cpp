#include "Common/Common.hpp"
#include "Math/Math.hpp"
#include "Graphics/ConstantBuffer/ShaderStageList.hpp"

#include "Graphics/GraphicDriverInfo/GraphicDriverInfo.hpp"
#include "Graphics/DisplayInfo/DisplayInfo.hpp"
#include "Graphics/Device/Device.hpp"
#include "Graphics/RenderTarget/RenderTarget.hpp"
#include "Graphics/Texture/Texture.hpp"
#include "Graphics/SwapChain/SwapChain.hpp"
#include "ToneCurve.hpp"
#include "Exception/Exception.hpp"

namespace Lobelia::Graphics {
	GammaCorrection::GammaCorrection(SwapChain* swap_chain) :gammacap{}, gammaControl{} {
		HRESULT hr = S_OK;
		hr = swap_chain->swapChain->GetContainingOutput(output.GetAddressOf());
		if (FAILED(hr))STRICT_THROW("�g�[���J�[�u�擾�Ɏ��s���܂���");
		hr = output->GetGammaControlCapabilities(&gammacap);
		if (FAILED(hr))STRICT_THROW("�K���}����@�\�擾�Ɏ��s���܂���");
	}
	GammaCorrection::~GammaCorrection() = default;
	void GammaCorrection::CurveSetting(float gamma, Utility::Color color_scale, Utility::Color color_offset) {
		//���̕ӂ�͌�قǏڂ����������邱��
		float renderTransform = 1.0f / gamma;
		gammaControl.Scale.Red = color_scale.r;
		gammaControl.Scale.Green = color_scale.g;
		gammaControl.Scale.Blue = color_scale.b;
		gammaControl.Offset.Red = color_offset.r;
		gammaControl.Offset.Green = color_offset.g;
		gammaControl.Offset.Blue = color_offset.b;
		for (int i = 0; i < gammacap.NumGammaControlPoints; i++) {
			float l0 = gammacap.ControlPointPositions[i];
			float l1 = pow(l0, gamma);
			gammaControl.GammaCurve[i].Red = l1;
			gammaControl.GammaCurve[i].Green = l1;
			gammaControl.GammaCurve[i].Blue = l1;
		}
	}
	void GammaCorrection::Set() { if (FAILED(output->SetGammaControl(&gammaControl)))STRICT_THROW("�K���}�̃Z�b�g�Ɏ��s"); }

}