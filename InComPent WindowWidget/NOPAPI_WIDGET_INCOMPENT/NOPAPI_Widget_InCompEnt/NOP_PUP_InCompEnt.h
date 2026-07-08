// ============================================================================
//                               
//
//                * * * * * * * * * * * * * * * * * * * * * * * *              
//                  --==>/  NOVATUORIA ORIGINAL PROJECT  \<==--                 
//                 --==>/  PROPER UNIVERSAL PERFORMANCES  \<==--                
//                --==>*    experimental  &  prototype     *<==--              
//               
//
//            NOP PUP Solutions: Internal Component for 1C Enterprise          
//               
//
//         Проект: NOP PUP InCompEnt 
//          Автор: Михайлова Александра (@novatuoria)
//         GitHub: https://github.com/novatuoria
//     Repository: https://github.com/novatuoria/nopapi_incompent
//        License: MIT
//
//                                   2026
//
// ============================================================================



#pragma once
#include "ComponentBase.h"
#include "AddInDefBase.h"
#include "IMemoryManager.h"

#include <string>
#include <string_view>

#include "NOP_PUP_WindowClass.h"



long GetClassObject(const WCHAR_T* wsName, IComponentBase** pInterface);

class CNPUP_INCOMPENT_NATIVE : public IComponentBase
{
public:
	enum MethodsInCompEnt
	{
		MICE_NONE = -1,
		// ----------------------------------------------------------------------------

		MICE_CREATE_WND,				// 0 +
		MICE_DISTROY_WND,				// 0 +
		MICE_REDRAW_WND,				// 0 +

		MICE_SETCLR_BKGR,				// 1 - булево +
		MICE_SETCLR_TEXT,				// 1 - булево +
		MICE_SETCLR_BRDR,				// 1 - булево +

		MICE_SET_TOPSIDE,				// 1 - булево +
		MICE_SET_MODDRAW,				// 1 - булево +
		MICE_SET_FIXPOS,				// 1 - булево +
		MICE_SET_MULTISTR,				// 1 - булево +
		MICE_SET_FIXSIZE,				// 1 - булево +
		MICE_SET_DRAWBRDR,				// 1 - булеов +
		MICE_SET_AUTORDRW,				// 1 - булеов +

		MICE_SETFNT_USERFONT,			// 1 - строка +
		MICE_SETFNT_ITALIC,				// 1 - булево +
		MICE_SETFNT_UNDERLINE,			// 1 - булево +
		MICE_SETFNT_STRIKELINE,			// 1 - булево +
		MICE_SETFNT_BOLDFONT,			// 1 - булево +

		MICE_SETSIZE_WINDOW,			// 2 - число высота и число ширина
		MICE_SETSIZE_TEXT,				// 1 - число
		MICE_SETSIZE_BORDER,			// 1 - число толщина

		MICE_SETDRAW_TEXT,				// 1 - строка +

		// ----------------------------------------------------------------------------
		MICE_FINAL
	};

private:
	IMemoryManager* m_iMemory = nullptr;
	IAddInDefBaseEx* m_iConnect = nullptr;

	CNPUP_WindowClass *cnpup_WndClass = nullptr;

public:

	CNPUP_INCOMPENT_NATIVE() = default;
	virtual ~CNPUP_INCOMPENT_NATIVE() = default;

	// IComponentBase
	virtual bool ADDIN_API Init(void *pInterface);
	virtual bool ADDIN_API setMemManager(void* mem);
	virtual long ADDIN_API GetInfo();
	virtual void ADDIN_API Done();

	// ILanguageExtenderBase
	virtual bool ADDIN_API RegisterExtensionAs(WCHAR_T** wsExtensionName);
	virtual long ADDIN_API GetNProps();
	virtual long ADDIN_API FindProp(const WCHAR_T* wsPropName);
	virtual const WCHAR_T* ADDIN_API GetPropName(long lPropNum, long lPropAlias);
	virtual bool ADDIN_API GetPropVal(const long lPropNum, tVariant* pvarPropVal);
	virtual bool ADDIN_API SetPropVal(const long lPropNum, tVariant* varPropVal);
	virtual bool ADDIN_API IsPropReadable(const long lPropNum);
	virtual bool ADDIN_API IsPropWritable(const long lPropNum);
	virtual long ADDIN_API GetNMethods();
	virtual long ADDIN_API FindMethod(const WCHAR_T* wsMethodName);
	virtual const WCHAR_T* ADDIN_API GetMethodName(const long lMethodNum,
		const long lMethodAlias);
	virtual long ADDIN_API GetNParams(const long lMethodNum);
	virtual bool ADDIN_API GetParamDefValue(const long lMethodNum, const long lParamNum,
		tVariant *pvarParamDefValue);
	virtual bool ADDIN_API HasRetVal(const long lMethodNum);
	virtual bool ADDIN_API CallAsProc(const long lMethodNum,
		tVariant* paParams, const long lSizeArray);
	virtual bool ADDIN_API CallAsFunc(const long lMethodNum,
		tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray);

	// LocaleBase
	virtual void ADDIN_API SetLocale(const WCHAR_T* loc);


};