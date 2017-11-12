#pragma once
namespace Lobelia::Graphics {
	/**
	*@brief �O���t�B�b�N�h���C�o�[�̏����擾���邽�߂̃N���X
	*/
	class GraphicDriverInfo {
		friend class GraphicDriverInfoList;
		friend class Device;
	private:
	private:
		DXGI_ADAPTER_DESC desc;
		ComPtr<IDXGIAdapter> adapter;
	public:
		GraphicDriverInfo(const ComPtr<IDXGIAdapter>& adapter);
		~GraphicDriverInfo();
		std::string GetDriverName()const noexcept;
		UINT GetVendorId()const noexcept;
		UINT GetDeviceId()const noexcept;
		UINT GetSubSysId()const noexcept;
		UINT GetRevision()const noexcept;
		size_t GetVideoMemory()const noexcept;
		size_t GetSystemMemory()const noexcept;
		size_t GetSharedSystemMemory()const noexcept;
		LUID GetLUID()const noexcept;
	};
	/**
	*@brief �O���t�B�b�N�h���C�o�[�̏���񋓂��邽�߂̃N���X
	*/
	class GraphicDriverInfoList {
	private:
		static ComPtr<IDXGIFactory> factory;
		static std::vector<std::shared_ptr<GraphicDriverInfo>> drivers;
		static int driverCount;
	public:
		/**@brief ���̊֐����Ăяo���Ȃ��Ə��͎��Ȃ�*/
		static void Bootup();
		/**@brief ���̊֐����Ăяo���Ǝ���Bootup()���ĂԂ܂ŏ��͎��Ȃ�*/
		static void Shutdown();
		static int GetGraphicDriverCount();
		static const std::shared_ptr<GraphicDriverInfo>& GetDriver(int index);
		static const std::vector<std::shared_ptr<GraphicDriverInfo>>& GetDrivers();
	};
}