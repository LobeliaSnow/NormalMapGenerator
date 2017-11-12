#pragma once

namespace Lobelia {
	/**
	*@brief ���\�[�X�}�l�[�W���[
	*@param �Ǘ��Ώۂ̌^
	*@param ���ƂȂ�^ �f�t�H���g�ł�std::string
	*/
	template<class T, class Key = std::string> class ResourceBank final {
	protected:
		/**
		*@brief ���\�[�X�Ǘ��p�A�z�z��
		*/
		static std::map<Key, std::shared_ptr<T>> resource;
	public:
		/**@brief �R���X�g���N�^*/
		ResourceBank()noexcept;
		/**@brief �f�X�g���N�^*/
		~ResourceBank()noexcept;
		/**
		*@brief �t�@�N�g���֐�
		*@brief �C���X�^���X������Ă���Ί����̂��̂��A����Ă��Ȃ���ΐV�K�ō쐬���ĕԂ��܂��B
		*@param <template>�C���X�^���X�쐬���ɓ��ꂽ�^�ƌp���֌W�̂��̂��Ǘ��������ꍇ�Ɏw��A���Ȃ���΂��̂܂܂̌^
		*@param <template>�C���X�^���X�쐬���Ɏg�p����������X�g
		*@param[in] ��
		*@param[in] �C���X�^���X�����ɕK�v�Ȉ���
		*@return �C���X�^���X�ւ̃|�C���^
		*/
		template<class U = T, class... Args> static T* Factory(Key key, Args... args);
		/**
		*@brief �o�^�֐�
		*@brief �t�@�N�g�����g�p�������ڃC���X�^���X��a�������Ƃ��Ɏg�p
		*@param[in] ��
		*@param[in] �C���X�^���X�ւ̃|�C���^
		*/
		static void Register(Key key, std::shared_ptr<T> p)noexcept;
		/**
		*@brief �C���X�^���X�����݂��邩�Ԃ�
		*@param[in] ��
		*@return ���݂��Ă��邩�ۂ���bool�l
		*/
		static bool IsExist(Key key)noexcept;
		static void Clear()noexcept;
		static T* Get(Key key)noexcept;
		static std::map<Key, std::shared_ptr<T>>& Get()noexcept;
		static void UnRegister(Key key)noexcept;
	};
}

#include "ResourceBank.inl"