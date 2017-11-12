#pragma once
#include "../D3DCompiler/d3dcompiler.h"
namespace Lobelia::Graphics {
	class ShaderCompiler {
	public:
		//BYTE* buffer�ɂ�new BYTE[*size]���ꂽ�l������̂ŁAdelete��Y��Ȃ��悤��
		//�V�������������Ĉȗ��A�e�X�g���Ă��Ȃ��̂ŐM���x�������Ⴂ�B
		[[deprecated("ReadCSO is deprecated.We recommend using a CompileShaderFromFile.")]]static void ReadCSO(const char* file_path, int* size, BYTE* buffer);
		static void CompileShaderFromFile(const char* file_path, const char* entry_point, const char* shader_model, ID3DBlob** blob);
		//TODO : FromMemory����邱�ƁB
	};
	class ShaderLinkageInstance final {
		friend class ShaderLinkage;
		friend void ShaderSet(std::function<void(int, ID3D11ClassInstance**)> functor, int instance_count, ShaderLinkageInstance* instances);
	private:
		std::string name;
		ComPtr<ID3D11ClassInstance> instance;
	public:
		ShaderLinkageInstance();
		~ShaderLinkageInstance();
		const std::string& GetName();
	};
	class ShaderLinkage final {
		friend class VertexShader;
		friend class PixelShader;
	private:
		ComPtr<ID3D11ClassLinkage> classLinkage;
	public:
		ShaderLinkage();
		~ShaderLinkage();
		//���t���N�V�������͌��
		//�N���X���Ƀf�[�^�����o�[�����݂��Ȃ��ۂɌĂяo��
		//�F�X�������K�v�ƂȂ肻��
		void CreateInstance(const char* instance_name, ShaderLinkageInstance* instance);
		//�N���X���Ƀf�[�^�����o�[�����݂���ۂɌĂяo��
		void GetInstance(const char* instance_name, int instance_index, ShaderLinkageInstance* instance);
	};

	//TODO : ��x�X�v���C�g���o�������蒼���B
	class Shader {
		friend class Reflection;
	protected:
		ComPtr<ID3DBlob> blob;
		std::unique_ptr<ShaderLinkage> linkage;
	public:
		Shader(const char* file_path, const char* entry_point, const char* shader_model, ShaderLinkage* linkage);
		~Shader();
		ShaderLinkage* GetLinkage();
	};

	class VertexShader :public Shader {
		friend class InputLayout;
		friend class Pipeline;
	public:
		enum Model { VS_2_0, VS_3_0, VS_4_0, VS_4_1, VS_5_0, VS_5_1, };
	private:
		ComPtr<ID3D11VertexShader> vs;
	private:
		//�V�F�[�_�[���f���̃p�[�X�B
		std::string ConverteShaderModelString(Model shader_model);
		void Set(int instance_count = 0, ShaderLinkageInstance* instances = nullptr);
	public:
		VertexShader(const char* file_path, const char* entry_point, Model shader_model, bool use_linkage = false);
		~VertexShader();
	};
	class PixelShader :public Shader {
		friend class Pipeline;
	public:
		enum Model { PS_2_0, PS_3_0, PS_4_0, PS_4_1, PS_5_0, PS_5_1, };
	private:
		ComPtr<ID3D11PixelShader> ps;
	private:
		//�V�F�[�_�[���f���̃p�[�X�B
		std::string ConverteShaderModelString(Model shader_model);
		void Set(int instance_count = 0, ShaderLinkageInstance* instances = nullptr);
	public:
		PixelShader(const char* file_path, const char* entry_point, Model shader_model, bool use_linkage = false);
		~PixelShader();
	};
}