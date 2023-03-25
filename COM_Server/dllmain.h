// dllmain.h: объявление класса модуля.

class CCOMServerModule : public ATL::CAtlDllModuleT< CCOMServerModule >
{
public :
	DECLARE_LIBID(LIBID_COMServerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COMSERVER, "{09955f16-7c0a-4652-b40d-5243d1508fcb}")
};

extern class CCOMServerModule _AtlModule;
