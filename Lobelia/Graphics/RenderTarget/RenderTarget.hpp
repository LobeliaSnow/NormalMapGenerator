#pragma once
namespace Lobelia::Graphics {
	class Texture;
	class RenderTarget {
	private:
		std::shared_ptr<Texture> texture;
		ComPtr<ID3D11RenderTargetView> renderTarget;
		std::shared_ptr<Texture> depth;
		ComPtr<ID3D11DepthStencilView> depthView;
	private:
		void CreateRenderTarget(const Math::Vector2& size, const DXGI_SAMPLE_DESC& sample);
		void CreateDepthView();
	public:
		RenderTarget(const Math::Vector2& size, const DXGI_SAMPLE_DESC& sample = { 1,0 }, const DXGI_FORMAT&  format = DXGI_FORMAT_R32G32B32A32_FLOAT);
		RenderTarget(const ComPtr<ID3D11Texture2D>& texture);
		~RenderTarget();
		Texture* GetTexture()const;
		void Clear(Utility::Color color);
		void ChangeDepthStencil(RenderTarget* view);
		void Activate();
		//TODO : ���������ɃZ�b�g�ł���悤��(MRT)
		//�[�x�o�b�t�@��0�Ԗڂ̂����g���܂�
		static void Activate(int rt_count, RenderTarget** rts);
	};
}