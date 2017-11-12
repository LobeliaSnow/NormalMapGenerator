#pragma once
namespace Lobelia::Utility {
	class FilePathControl {
	public:
		static std::string GetExtension(const std::string& file_path);
		static std::string GetFilename(const std::string& file_path);
		static std::string GetRootDirectory(const std::string& file_path);
		static std::string GetParentDirectory(const std::string& file_path);
		static std::string GetRelativeDirectory(const std::string& file_path);
		//���ɂ����낢��ǉ��\��
	};
}