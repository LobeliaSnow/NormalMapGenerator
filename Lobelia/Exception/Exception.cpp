#include "Common/Common.hpp"
#include "Exception.hpp"


namespace Lobelia {
	std::string Exception::CreateMessage()const noexcept {
		std::stringstream error;
		error << "\n======! begin exception message !======\n\n" << "\n[source : " << _filename << "]\n\n[function : " << _functionName << "]\n\n[line : " << _executeLine << "]\n\n";
		if (!_msg.empty())error << "[cause : " << _msg << "]\n\n";
		error << "\n======! end exception message !======\n\n";
		return error.str();
	}
	void Exception::OutputLog()const noexcept {  }
	Exception::Exception(std::string filename, std::string func_name, int exe_line) noexcept :Exception(filename, func_name, exe_line, "") {}
	Exception::Exception(std::string filename, std::string func_name, int exe_line, std::string msg) noexcept : _filename(filename), _functionName(func_name), _executeLine(exe_line), _msg(msg) {}
	Exception::~Exception() noexcept = default;
	void Exception::ConsoleMessage()const noexcept {
#if (defined(__EXCEPTION_ON__)||defined(__STRICT_EXCEPTION_ON__))&&!defined(__NO_EXCEPTION__)
		std::cout << CreateMessage() << std::endl;
#endif
		OutputLog();
	}
	void Exception::VsConsoleMessage()const noexcept {
#if (defined(__EXCEPTION_ON__)||defined(__STRICT_EXCEPTION_ON__))&&!defined(__NO_EXCEPTION__)
		OutputDebugStringA(CreateMessage().c_str());
#endif
		OutputLog();
	}
	void Exception::BoxMessage()const noexcept {
#if (defined(__EXCEPTION_ON__)||defined(__STRICT_EXCEPTION_ON__))&&!defined(__NO_EXCEPTION__)
		MessageBoxA(nullptr, CreateMessage().c_str(), "exception!", MB_OK | MB_ICONERROR);
#endif
		OutputLog();
	}
	const std::string Exception::GetExceptionMessage()const noexcept { return CreateMessage(); }

	/**
	*@brief �G���[�`�F�b�N
	*@brief �G���[���ɃG���[������,false��Ԃ��A�����łȂ����ture��Ԃ�
	*@attention �܂��܂��������A�K�v�ƂȂ������̂��o����X�V���Ă���<br>�p�ꂪ�����������Ŗ|��\�t�g�g���Ă镔������A�����������񂵂����Lobelia�܂�<br>�ԈႢ���񍐂��肢���܂�
	*@param[in] errno_t
	*@return bool
	*/
	bool ErrnoCheck(errno_t err) noexcept {
		TRY{
			switch (err) {
			case 0:				break;
				//��/usr/include/asm-generic/errno-base.h
			case EPERM:								STRICT_THROW("����͋�����Ă��܂���?/n����(Operation not permitted)");
			case ENOENT:							STRICT_THROW("�t�@�C���܂��̓f�B���N�g�������݂��܂���");
			case ESRCH:								STRICT_THROW("���̂悤�ȃv���Z�X�͂���܂���?/n����(No such process)");
			case EINTR:								STRICT_THROW("�V�X�e���R�[�������f����܂���");
			case EIO:									STRICT_THROW("I/O�G���[");
			case ENXIO:								STRICT_THROW("�f�o�C�X��A�h���X������܂���");
			case E2BIG:								STRICT_THROW("�������X�g���������܂�");
			case ENOEXEC:							STRICT_THROW("���s�`���G���[?/n����(Exec format error)");
			case EBADF:								STRICT_THROW("�t�@�C���ԍ�������������܂���");
			case ECHILD:								STRICT_THROW("�q�v���Z�X�͂���܂���");
			case EAGAIN:								STRICT_THROW("�Ď��s���Ă�������");
			case ENOMEM:							STRICT_THROW("�������s���ł�?/n����(Out of memory)");
			case EACCES:								STRICT_THROW("�A�N�Z�X�����ۂ���܂���");
			case EFAULT:								STRICT_THROW("�A�h���X������������܂���");
				//case ENOTBLK:						throw"Block device required";
			case EBUSY:								STRICT_THROW("�f�o�C�X�܂��̓��\�[�X���r�W�[��Ԃł�");
			case EEXIST:								STRICT_THROW("�t�@�C�������݂��Ă��܂�");
			case EXDEV:								STRICT_THROW("�N���X�f�o�C�X�����N?/n����(Cross-device link)");
			case ENODEV:							STRICT_THROW("�f�o�C�X�����݂��܂���");
			case ENOTDIR:							STRICT_THROW("�f�B���N�g���ł͂���܂���");
			case EISDIR:								STRICT_THROW("�f�B���N�g���ł�?/n����(Is a directory)");
			case EINVAL:								STRICT_THROW("�����Ȉ����ł�");
			case ENFILE:								STRICT_THROW("�t�@�C���e�[�u���I�[�o�[�t���[?/n����(File table overflow)");
			case EMFILE:								STRICT_THROW("�J���Ă���t�@�C�����������܂�");
			case ENOTTY:							STRICT_THROW("�^�C�v���C�^�[�ł͂���܂���?/n����(Not a typewriter)");
			case ETXTBSY:							STRICT_THROW("�e�L�X�g�t�@�C�����r�W�[��Ԃł�");
			case EFBIG:								STRICT_THROW("�t�@�C���̃T�C�Y���傫�����܂�");
			case ENOSPC:							STRICT_THROW("�f�o�C�X�ɃX�y�[�X���c���Ă��܂���?/n����(No space left on device)");
			case ESPIPE:								STRICT_THROW("�s���ȃV�[�N�ł�");
			case EROFS:								STRICT_THROW("�ǂݎ���p�̃V�X�e���t�@�C���ł�");
			case EMLINK:							STRICT_THROW("�����N���������܂�");
			case EPIPE:								STRICT_THROW("�p�C�v�����Ă��܂�?/n����(Broken pipe)");
			case EDOM:								STRICT_THROW("��s��/n����(Math argument out of domain of func)");
			case ERANGE:							STRICT_THROW("���w�I���ʂ��\���ł��܂���?/n����(Math result not representable)");
				//��/usr/include/asm-generic/errno.h
			case EDEADLK:							STRICT_THROW("���\�[�X�̃f�b�h���b�N���������Ă��܂�");
			case ENAMETOOLONG:			STRICT_THROW("�t�@�C�������������܂�");
			case ENOLCK:							STRICT_THROW("�g�p�\�ȃ��R�[�h���b�N������܂���?/n����(No record locks available)");
			case ENOSYS:							STRICT_THROW("�@�\����������Ă܂���");
			case ENOTEMPTY:						STRICT_THROW("�f�B���N�g��������ł͂���܂���");
			case ELOOP:								STRICT_THROW("�V���{���b�N�����N���������܂�");
			case EWOULDBLOCK:				STRICT_THROW("���삪�u���b�N����܂���");
			case ENOMSG:							STRICT_THROW("��]�^�C�v�̃��b�Z�[�W������܂���?/n����(No message of desired type)");
			case EIDRM:								STRICT_THROW("���ʎq���폜����܂���?/n����(Identifier removed)");
			case ENOTSOCK:						STRICT_THROW("��\�P�b�g�ł̃\�P�b�g����");
			case EDESTADDRREQ:				STRICT_THROW("����A�h���X���K�v�ł�");
			case EMSGSIZE:							STRICT_THROW("���b�Z�[�W���������܂�");
			case EPROTOTYPE:					STRICT_THROW("�\�P�b�g�̃v���g�R���^�C�v���Ԉ���Ă��܂�");
			case ENOPROTOOPT:				STRICT_THROW("�v���g�R�������p�ł��܂���");
			case EPROTONOSUPPORT:		STRICT_THROW("Protocol not supported");
			case EOPNOTSUPP:					STRICT_THROW("�g�����X�|�[�g�G���h�|�C���g�ŃT�|�[�g����Ă��Ȃ�����?/n����(Operation not supported on transport endpoint)");
			case EAFNOSUPPORT:				STRICT_THROW("�A�h���X�t�@�~���̓v���g�R���ŃT�|�[�g����Ă��܂���");
			case EADDRINUSE:					STRICT_THROW("�A�h���X�͊��Ɏg�p����Ă��܂�");
			case EADDRNOTAVAIL:				STRICT_THROW("�v�����ꂽ�A�h���X�����蓖�Ă邱�Ƃ��ł��܂���");
			case ENETDOWN:						STRICT_THROW("�l�b�g���[�N�������Ă��܂�");
			case ENETUNREACH:				STRICT_THROW("�l�b�g���[�N�ɓ��B�ł��܂���");
			case ENETRESET:						STRICT_THROW("���Z�b�g�ɂ��l�b�g���[�N�ڑ��̐ؒf");
			case ECONNABORTED:				STRICT_THROW("�\�t�g�E�F�A�ɂ��ڑ��̒��~");
			case ECONNRESET:					STRICT_THROW("�s�A�ɂ��ڑ����Z�b�g");
			case ENOBUFS:							STRICT_THROW("�o�b�t�@�̋󂫂�����܂���");
			case EISCONN:							STRICT_THROW("�g�����X�|�[�g�G���h�|�C���g�͊��ɐڑ�����Ă��܂�?/n����(Transport endpoint is already connected)");
			case ENOTCONN:						STRICT_THROW("�g�����X�|�[�g�G���h�|�C���g���ڑ�����Ă��܂���?/n����(Transport endpoint is not connected)");
			case ETIMEDOUT:						STRICT_THROW("�ڑ����^�C���A�E�g���܂���");
			case ECONNREFUSED:				STRICT_THROW("�ڑ������ۂ���܂���");
			default:										STRICT_THROW("�G���[/n�G���[���e���o�^/n");
			}
		}CATCH(Exception& e) {
			e.BoxMessage();
			return false;
		}
		return true;
	}

}