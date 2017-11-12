#pragma once
#include "../DirectXTex/DirectXTex.h"

#ifdef _DEBUG
#pragma comment(lib,"DirectXTexDebug.lib")
#else
#pragma comment(lib,"DirectXTexRelease.lib")
#endif

namespace Lobelia::Graphics {
	class Texture final {
		friend class TextureFileAccessor;
		friend class RenderTarget;
	private:
		Math::Vector2 size;
		ComPtr<ID3D11ShaderResourceView> view;
		ComPtr<ID3D11Texture2D> texture;
	private:
		//�����v����
		void CreateTexture(DXGI_FORMAT format, UINT bind_flags, const DXGI_SAMPLE_DESC& sample);
		void CreateShaderResourceView(DXGI_FORMAT format);
	public:
		Texture(const Math::Vector2& size, DXGI_FORMAT format, UINT bind_flags, const DXGI_SAMPLE_DESC& sample);
		Texture(const ComPtr<ID3D11Texture2D>& texture);
		~Texture();
		ComPtr<ID3D11Texture2D>& Get();
		const Math::Vector2& GetSize();
		//TODO : �Z�b�g��p�ӂ��邱�ƁA���̍ۑ|���̂��Ƃ��C��t���邱��
		//�������_�[�^�[�Q�b�g�ƃV�F�[�_�[���\�[�X�r���[���������ɃZ�b�g����Ă��܂��󋵂ɂȂ��Ă��܂��Ƃ܂����̂ł���̉��
		void Set(int num_slot, ShaderStageList list);
		void Clean(int num_slot, ShaderStageList list);
	};
	//����������
	//IWICBitmapDecoder::GetFrame
	//DirectX::ComputeNormalMap
	//DirectX::IsVideo
	class TextureFileAccessor final {
	public:
		enum class Extension {
			NO_SUPPORT = -1,
			PNG,
			JPG,
			TGA,
			BMP,
		};
	private:
		static void LoadFile(const wchar_t* file_path, Extension extension, DirectX::TexMetadata* meta, DirectX::ScratchImage& image);
	public:
		static Extension JudgeExtension(const std::string& file_path);
		static void Load(const char* file_path, Texture** texture);
		//�ۑ��@�\�ǉ��\��
		static void Save(const char* file_path, Texture* texture);
		static void CreateNormalMap(Texture* src, Texture* normal, float amplitude, DWORD flags = DirectX::CNMAP_DEFAULT);
	};
}