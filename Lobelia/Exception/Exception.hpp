#pragma once
#ifndef __HDX_EXCEPTION__
#define __HDX_EXCEPTION__
#ifdef _DEBUG
//����͗�O�������Ɏw�肳�ꂽ�����ŏ���\������
#define __EXCEPTION_ON__
//����̓��O���͂��悤�ɂ���
#define __EXCEPTION_LOG_ON__
#endif
//�w�肳�ꂽ��O�ƃ��O�t�@�C���𗼕��͂�����
//#define __STRICT_EXCEPTION_ON__
//������`�����Exception�̓��O�t�@�C������O�������Ȃ�
//��ԗD��x������ �ق��̃R�}���h�����ׂĖ�������
//#define __NO_EXCEPTION__

namespace Lobelia {
	/**
	*@brief ��O�N���X
	*@brief �ꉞ�n�k�Ŏ��̂�����Ďg�p���邱�Ƃ��\
	*@attention ���̃N���X�͎����Ŏ��̂𐶐�����̂ł͂Ȃ��A<br>
	*���Œ�`����Ă���}�N���ɂ���Đ���������B<br>
	*���b�Z�[�W��\������ɂ́ACATCH���ł��̃N���X��߂܂��ă����o�֐��ɂ���ĕ\��
	*@attention ���O�o�͓��̐���͏�ɂ���R�����g�Q��
	*/
	class Exception final{
	private:
		/**@brief �\�[�X�t�@�C����*/
		std::string _filename;
		/**@brief ���s���ꂽ�֐���*/
		std::string _functionName;
		/**@brief ��O���o���s*/
		int _executeLine;
		/**@brief �C�ӂ̃��b�Z�[�W*/
		std::string _msg;
	private:
		/**
		*@brief �G���[���b�Z�[�W�\�z
		*@return �G���[����
		*/
		std::string CreateMessage()const noexcept;
		/**
		*@brief ���O�o��
		*/
		void OutputLog()const noexcept;
	public:
		/**
		*@brief �R���X�g���N�^
		*@param[in] �\�[�X�t�@�C����
		*@param[in] �֐���
		*@param[in] ���s�s�ԍ�
		*/
		Exception(std::string filename, std::string func_name, int exe_line) noexcept;
		/**
		*@brief �R���X�g���N�^
		*@param[in] �\�[�X�t�@�C����
		*@param[in] �֐���
		*@param[in] ���s�s�ԍ�
		*@param[in] �C�ӂ̃��b�Z�[�W
		*/
		Exception(std::string filename, std::string func_name, int exe_line, std::string msg) noexcept;
		/**@brief �f�X�g���N�^*/
		virtual ~Exception() noexcept;
		/**@brief �R���\�[���ɏo��*/
		void ConsoleMessage()const noexcept;
		/**@brief VisualStudio�̏o�͑��ɏo��*/
		void VsConsoleMessage()const noexcept;
		/**@brief ���b�Z�[�W�{�b�N�X�ɂ��o��*/
		void BoxMessage()const noexcept;
		/**@brief �G���[���͂��擾*/
		const std::string GetExceptionMessage()const noexcept;
	};
}

//���̐�}�N����`
/**@def ��O�N���X���̐���*/
#define STRICT_EXCEPTION_FACTORY(msg) Lobelia::Exception(FILE_NAME,FUNCTION_NAME,EXECUTE_LINE,msg)
/**@def ��O�N���X���̐���*/
#define EXCEPTION_FACTORY STRICT_EXCEPTION_FACTORY("")
/**@def try*/
#define TRY try
/**@def throw Exception�����b�Z�[�W�t���œ�����*/
#define STRICT_THROW(msg) throw STRICT_EXCEPTION_FACTORY(msg)
/**@def throw Exception�𓊂���*/
#define THROW_E STRICT_THROW("");

namespace Lobelia {
	bool ErrnoCheck(errno_t err) noexcept;
}
#endif