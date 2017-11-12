#pragma once
namespace Lobelia::Graphics {
	//�t���X�N�̂ݎg���܂�
	class GammaCorrection {
	private:
		ComPtr<IDXGIOutput> output;
		DXGI_GAMMA_CONTROL_CAPABILITIES gammacap;
		DXGI_GAMMA_CONTROL gammaControl;
	public:
		GammaCorrection(SwapChain* swap_chain);
		~GammaCorrection();
		//Color�^�̃A���t�@�͖�������܂�
		void CurveSetting(float gamma, Utility::Color color_scale, Utility::Color color_offset);
		void Set();
	};
}