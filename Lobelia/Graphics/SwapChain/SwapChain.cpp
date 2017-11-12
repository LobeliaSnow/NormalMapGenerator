#include "Common/Common.hpp"
#include "Math/Math.hpp"
#include "Graphics/ConstantBuffer/ShaderStageList.hpp"

#include "Graphics/GraphicDriverInfo/GraphicDriverInfo.hpp"
#include "Graphics/DisplayInfo/DisplayInfo.hpp"
#include "Graphics/Device/Device.hpp"
#include "Graphics/RenderTarget/RenderTarget.hpp"
#include "Graphics/Texture/Texture.hpp"
#include "Graphics/SwapChain/SwapChain.hpp"
#include "Exception/Exception.hpp"

namespace Lobelia::Graphics {
	SwapChain::SwapChain(Window* window, DXGI_SAMPLE_DESC sample_desc, DisplayInfo* info) {
		if (!window)STRICT_THROW("�C���X�^���X�Ώۂ��ݒ肳��Ă��܂���");
		int refreshRate = 60;
		if (info)refreshRate = info->GetRefreshRate();
		CreateSwapChain(window, sample_desc, refreshRate);
		ComPtr<ID3D11Texture2D> backBuffer;
		HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
		if (FAILED(hr))STRICT_THROW("�o�b�N�o�b�t�@�̎擾�Ɏ��s���܂���");
		renderTarget = std::make_shared<RenderTarget>(backBuffer);
		renderTarget->Activate();
	}
	SwapChain::SwapChain(HWND hwnd, const Math::Vector2& size, DXGI_SAMPLE_DESC sample_desc, DisplayInfo* info) {
		int refreshRate = 60;
		if (info)refreshRate = info->GetRefreshRate();
		CreateSwapChain(hwnd, size, sample_desc, refreshRate);
		ComPtr<ID3D11Texture2D> backBuffer;
		HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
		if (FAILED(hr))STRICT_THROW("�o�b�N�o�b�t�@�̎擾�Ɏ��s���܂���");
		renderTarget = std::make_shared<RenderTarget>(backBuffer);
		renderTarget->Activate();
	}

	SwapChain::~SwapChain() { swapChain->SetFullscreenState(false, nullptr); }
	void SwapChain::CreateSwapChain(Window* window, DXGI_SAMPLE_DESC sample_desc, int refresh_rate) {
		CreateSwapChain(window->GetHandle(), window->GetSize(), sample_desc, refresh_rate);
	}
	void SwapChain::CreateSwapChain(HWND hwnd, const Math::Vector2& size, DXGI_SAMPLE_DESC sample_desc, int refresh_rate) {
		ComPtr<IDXGIFactory> factory;
		CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(factory.GetAddressOf()));

		DXGI_SWAP_CHAIN_DESC desc = {};
		desc.BufferDesc.Width = size.x;
		desc.BufferDesc.Height = size.y;
		desc.BufferDesc.RefreshRate.Numerator = refresh_rate;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		//�����Ɋւ��Ă͗v���k
		desc.SampleDesc = sample_desc;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		HRESULT hr = factory->CreateSwapChain(Device::Get().Get(), &desc, swapChain.GetAddressOf());
		if (FAILED(hr))STRICT_THROW("�X���b�v�`�F�C���̍쐬�Ɏ��s");
	}

	DXGI_SAMPLE_DESC SwapChain::SearchLevelMSAA() {
		HRESULT hr = S_OK;
		DXGI_SAMPLE_DESC msaa = {};
		UINT quality = 0;
		//�@�\�̍ő僌�x���擾
		for (int i = 1; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i <<= 1) {
			hr = Device::Get()->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, i, &quality);
			if (SUCCEEDED(hr) && quality > 0) {
				msaa.Count = i;
				msaa.Quality = quality - 1;
			}
		}
		return msaa;
	}
	RenderTarget* SwapChain::GetRenderTarget() { return renderTarget.get(); }
	void SwapChain::Clear(Utility::Color color) { renderTarget->Clear(color); }
	void SwapChain::Present() { swapChain->Present(0, 0); }

}