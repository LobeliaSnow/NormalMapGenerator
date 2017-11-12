#pragma once
#define HDX_2017 "HDX_Engine"
#define HDX_VERSION HDX_2017
#define APPLICATION_NAME HDX_VERSION

//�f�t�H���g�̃V�F�[�_�[�̓o�^��
//VS
#define DEFAULT_VERTEX_SHADER_SPRITE "VS2D"
#define DEFAULT_VERTEX_SHADER_BATCH "VS2DINST"
#define DEFAULT_VERTEX_SHADER_STATIC_MODEL "VS3D"
#define DEFAULT_VERTEX_SHADER_DYNAIMC_MODEL "VS3DS"
//PS
#define DEFAULT_PIXEL_SHADER_2D "PS2D"
#define DEFAULT_PIXEL_SHADER_3D "PS3D"

//�f�t�H���g�p�C�v���C���̓o�^��
#define DEFAULT_PIPELINE_SPRITE "Default2DSprite"
#define DEFAULT_PIPELINE_BATCH "Default2DBatch"
#define DEFAULT_PIPELINE_STATIC_MODEL "Default3D"
#define DEFAULT_PIPELINE_DYNAMIC_MODEL "Default3DSkin"

//�C���X�^���X��...�V�F�[�_�[�̃N���X���Ɠ����ł���K�v������
#define PIXEL_INSTANCE_NAME_TEXTURE "TextureColor"
#define PIXEL_INSTANCE_NAME_VERTEX "VertexColor"
#define PIXEL_INSTANCE_NAME_INVERT_TEXTURE "InvertTextureColor"
#define PIXEL_INSTANCE_NAME_GRAYSCALE_TEXTURE "GrayscaleTextureColor"
#define PIXEL_INSTANCE_NAME_SEPIA_TEXTURE  "SepiaTextureColor"

//�����P�[�W�C���X�^���X�̃|�C���^�擾
//��قǂǂ����Ƀt�B�[���h��p�ӂ��ă}�b�v���o�R���Ȃ��悤�ɂ���
#define PIXEL_INSTANCE_TEXTURE Lobelia::ResourceBank<Lobelia::Graphics::ShaderLinkageInstance>::Get(PIXEL_INSTANCE_NAME_TEXTURE)
#define PIXEL_INSTANCE_VERTEX Lobelia::ResourceBank<Lobelia::Graphics::ShaderLinkageInstance>::Get(PIXEL_INSTANCE_NAME_VERTEX)
#define PIXEL_INSTANCE_INVERT_TEXTURE Lobelia::ResourceBank<Lobelia::Graphics::ShaderLinkageInstance>::Get(PIXEL_INSTANCE_NAME_INVERT_TEXTURE)
#define PIXEL_INSTANCE_GRAYSCALE_TEXTURE Lobelia::ResourceBank<Lobelia::Graphics::ShaderLinkageInstance>::Get(PIXEL_INSTANCE_NAME_GRAYSCALE_TEXTURE)
#define PIXEL_INSTANCE_SEPIA_TEXTURE Lobelia::ResourceBank<Lobelia::Graphics::ShaderLinkageInstance>::Get(PIXEL_INSTANCE_NAME_SEPIA_TEXTURE)

//�X�e���V���I�t
#define STENCIL_STATE_OFF_Z_OFF "Z Off Stencil Off"
#define STENCIL_STATE_OFF_Z_ON "Z On Stencil Off"
//�^�����p�̌^�쐬�p
#define STENCIL_STATE_WRITE_Z_OFF "Z Off Stencil Write"
#define STENCIL_STATE_WRITE_Z_ON "Z On Stencil Write"
//�쐬�����^�̒��ɂ̂ݕ`��
#define STENCIL_STATE_READ_Z_OFF "Z Off Stencil Read"
#define STENCIL_STATE_READ_Z_ON "Z On Stencil Read"

#define Interface abstract

#define s_cast static_cast
#define f_cast s_cast<float>
#define i_cast s_cast<int>
#define r_cast reinterpret_cast
#define d_cast dynamic_cast

/**@def �\�[�X�t�@�C�����擾*/
#define FILE_NAME __FILE__
/**@def �֐����擾*/
#define FUNCTION_NAME __func__
/**@def ���s���Ă���s�擾*/
#define EXECUTE_LINE __LINE__
/**@def �ϐ����擾*/
#define VARIABLE_NAME(variable) # variable
/**@def catch*/
#define CATCH catch
/**@def throw*/
#define THROW throw
/**@def �A���C�����g*/
#define ALIGN(n) __declspec(align(n))
