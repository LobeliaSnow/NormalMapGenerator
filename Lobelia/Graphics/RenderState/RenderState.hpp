#pragma once
namespace Lobelia::Graphics {
	enum class BlendPreset { MIN = -1, NONE, COPY, ADD, SUB, REPLACE, MULTIPLY, LIGHTENESS, DARKENESS, SCREEN, MAX };
	enum class SamplerPreset { MIN, POINT, LINEAR, ANISOTROPIC, COMPARISON_POINT, COMPARISON_LINEAR, COMPARISON_ANISOTROPIC, MAX, };
	enum class RasterizerPreset { MIN, FRONT, BACK, NONE, MAX, };
	enum class DepthPreset { MIN, NEVER, LESS, EQUAL, LESS_EQUAL, GREATER, NOT_EQUAL, GREATER_EQUAL, ALWAYS, MAX, };
	struct StencilDesc {
		//�ǂݏ������Ȃ��Ƃ���0���w�肵�ĂˁB
		UINT8 readMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		UINT8 writeMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		struct Face {
			enum class Operation :BYTE { KEEP = D3D11_STENCIL_OP_KEEP, ZERO = D3D11_STENCIL_OP_ZERO, REPLACE = D3D11_STENCIL_OP_REPLACE, INCR_CLAMP = D3D11_STENCIL_OP_INCR_SAT, DECR_CLAMP = D3D11_STENCIL_OP_DECR_SAT, INVERT = D3D11_STENCIL_OP_INVERT, INCR_WRAP = D3D11_STENCIL_OP_INCR, DECR_WRAP = D3D11_STENCIL_OP_DECR };
			//�e�X�g���s
			Operation faile;
			//�[�x�e�X�g���s
			Operation depthFail;
			//�e�X�g���i
			Operation pass;
			//���� �\�[�X�l �E�� �X�e���V���l
			enum class Function :BYTE { ALWAYS_FAIL = D3D11_COMPARISON_NEVER, LESS = D3D11_COMPARISON_LESS, EQUAL = D3D11_COMPARISON_EQUAL, LESS_EQUAL = D3D11_COMPARISON_LESS_EQUAL, GREATER = D3D11_COMPARISON_GREATER, NOT_EQUAL = D3D11_COMPARISON_NOT_EQUAL, GREATER_EQUAL = D3D11_COMPARISON_GREATER_EQUAL, ALWAYS_PASS = D3D11_COMPARISON_ALWAYS };
			//�X�e���V���e�X�g���s���֐�
			Function testFunc;
		};
		Face front;
		Face back;
	};
	using StencilOperation = StencilDesc::Face::Operation;
	using StencilFunction = StencilDesc::Face::Function;
	class BlendState final :private Origin<BlendState> {
		friend class Pipeline;
	private:
		/**@brief �u�����h�X�e�[�g�{��*/
		ComPtr<ID3D11BlendState> state;
	private:
		void SettingPreset(D3D11_BLEND_DESC* desc, int preset)const;
		void Set(bool force_set = false)noexcept;
	public:
		//�쐬�Ɏ��s�����ꍇ�AException�^�ŗ�O�𓊂��܂�
		BlendState(BlendPreset preset, bool blend, bool alpha_coverage);
		~BlendState();
	};
	class SamplerState final :private Origin<SamplerState> {
		friend class Pipeline;
	private:
		/**@brief �T���v���[�X�e�[�g�{��*/
		ComPtr<ID3D11SamplerState> state;
	private:
		void SettingPreset(D3D11_SAMPLER_DESC* desc, int preset)const;
		void Set(bool force_set = false)noexcept;
	public:
		//�쐬�Ɏ��s�����ꍇ�AException�^�ŗ�O�𓊂��܂�
		SamplerState(SamplerPreset preset, int max_anisotropy);
		~SamplerState();
	};
	class RasterizerState final :private Origin<RasterizerState> {
		friend class Pipeline;
	private:
		/**@brief ���X�^���C�U�[�X�e�[�g�{��*/
		ComPtr<ID3D11RasterizerState> state;
	private:
		void SettingPreset(D3D11_RASTERIZER_DESC* desc, int preset)const;
		void Set(bool force_set = false)noexcept;
	public:
		//�쐬�Ɏ��s�����ꍇ�AException�^�ŗ�O�𓊂��܂�
		RasterizerState(RasterizerPreset preset, bool wire_frame = false);
		~RasterizerState();
	};
	class DepthStencilState final :private Origin<DepthStencilState> {
		friend class Pipeline;
	private:
		ComPtr<ID3D11DepthStencilState> state;
	private:
		void SettingPreset(D3D11_DEPTH_STENCIL_DESC* desc, int preset)const;
		void Set(bool force_set = false)noexcept;
	public:
		//�쐬�Ɏ��s�����ꍇ�AException�^�ŗ�O�𓊂��܂�
		//stencil���܂��悭�킩���Ă��Ȃ��B
		DepthStencilState(DepthPreset preset, bool depth, StencilDesc sdesc, bool stencil);
		~DepthStencilState();
	};

	class RenderStateBank final {
	public:
		RenderStateBank() = delete;
		~RenderStateBank() = delete;
		RenderStateBank(const RenderStateBank&) = delete;
		RenderStateBank(RenderStateBank&&) = delete;
		static void BlendFactory(std::string key, BlendPreset p, bool blend_enable, bool alpha_coverage)noexcept;
		static void SamplerFactory(std::string key, SamplerPreset p, int max_anisotropy = 16);
		static void RasterizerFactory(std::string key, RasterizerPreset p, bool wire_frame = false);
		static void DepthStencilFactory(std::string key, DepthPreset p, bool depth, StencilDesc desc, bool stencil);
	};

}