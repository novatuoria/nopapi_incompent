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



#include "pch.h"
#include "NOP_PUP_InCompEnt.h"



#define NOPAPI_NAMEINCOMPENT L"NPUP_InCompEnt_WindowWidget"


#pragma region XMACRO
// ----------------  STRING NAME AND COUNT PARAM METHODS X-MACRO  --------------
//
// MASK: enum MethodsInCompEnt, String name EN, String name RU, Count in-param
//
#define METHOD_LIST	\
    MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_CREATE_WND,			L"CreateWindow",  L"СоздатьОкно",				0) \
    MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_DISTROY_WND,			L"DestroyWindow", L"УничтожитьОкно",			0) \
    MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_REDRAW_WND, 			L"RedrawWindow", L"ОбновитьОкно",				0) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETCLR_BKGR,		L"SetDefaultColorWindow", L"ВыбратьЦветФонаОкна",		1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETCLR_TEXT,		L"SetDefaultColorText", L"ВыбратьЦветТекста",			1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETCLR_BRDR,		L"SetDefaultColorBorder", L"ВыбратьЦветГраницыОкна",	1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SET_TOPSIDE,			L"SetTopSideWindow", L"УстановитьПоверхВсехОкон",		1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SET_MODDRAW,			L"SetModDraw", L"УстановитьВыводФонаОкна",				1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SET_FIXPOS,			L"FixPositionWindow", L"ФиксироватьПоложениеОкна",		1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SET_MULTISTR,		L"MultiStringText", L"МногострочныйРежимВыводаТекста",		1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SET_FIXSIZE,			L"FixSizeWindow", L"ФиксированныйРазмерОкна",		1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SET_DRAWBRDR,		L"DrawBorder", L"РисоватьГраницуОкна",					1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SET_AUTORDRW,		L"AutoDraw", L"РисоватьАвтоматически",					1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETFNT_USERFONT,			L"UserFont", L"ВыбратьШрифт",					1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETFNT_ITALIC,			L"ItalicFont", L"КурсивныйШрифт",				1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETFNT_UNDERLINE,		L"UnderLineFont", L"ПодчеркнутыйШрифт",				1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETFNT_STRIKELINE,		L"StrikeLineFont", L"ЗачеркнутыйШрифт",			1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETFNT_BOLDFONT,			L"BoldFont", L"ЖирныйШрифт",					1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETSIZE_WINDOW,		L"SetSizeWindow", L"УстановитьРазмерОкна",			2) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETSIZE_TEXT,		L"SetHeightFont", L"УстановитьВысотуШрифта",			1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETSIZE_BORDER,		L"SetDepthBorder", L"УстановитьТолщинуГраницы",		1) \
	MTHDL(CNPUP_INCOMPENT_NATIVE::MICE_SETDRAW_TEXT,	L"SetText", L"ВывестиТекст",								1)
// ----------------------------------------------------------------------------

// ------------------  STRING NAME DEFAULT COLOR WINDOWWIDGET  ----------------
//
// MASK: enum ColorElementWnd, String name EN, String name RU
//
#define COLOR_LIST	\
    CLR(CNPUP_WindowClass::CEW_BLACK,	L"BLACK",	L"ЧЕРНЫЙ")		\
    CLR(CNPUP_WindowClass::CEW_RED,		L"RED",		L"КРАСНЫЙ")		\
    CLR(CNPUP_WindowClass::CEW_ORANGE,	L"ORANGE",	L"ОРАНЖЕВЫЙ")	\
    CLR(CNPUP_WindowClass::CEW_YELLOW,	L"YELLOW",	L"ЖЕЛТЫЙ")		\
	CLR(CNPUP_WindowClass::CEW_GREEN,	L"GREEN",	L"ЗЕЛЕНЫЙ")		\
	CLR(CNPUP_WindowClass::CEW_BLUE,	L"BLUE",	L"СИНИЙ")		\
	CLR(CNPUP_WindowClass::CEW_VIOLET,	L"VIOLET",	L"ФИОЛЕТОВЫЙ")	\
	CLR(CNPUP_WindowClass::CEW_INDIGO,	L"INDIGO",	L"РОЗОВЫЙ")		\
	CLR(CNPUP_WindowClass::CEW_MAGENTA,	L"MAGENTA", L"ПУРПУРНЫЙ")	\
	CLR(CNPUP_WindowClass::CEW_WHITE,	L"WHITE",	L"БЕЛЫЙ")
// ----------------------------------------------------------------------------
#pragma endregion


uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len = 0);

// ----------------------------------------------------------------------------

uint32_t convToShortWchar
(
	WCHAR_T** Dest,
	const wchar_t* Source,
	uint32_t len
)
{
	if (!len)
		len = ::wcslen(Source) + 1;

	if (!*Dest)
		*Dest = new WCHAR_T[len];

	WCHAR_T* tmpShort = *Dest;
	wchar_t* tmpWChar = (wchar_t*)Source;
	uint32_t res = 0;

	::memset(*Dest, 0, len * sizeof(WCHAR_T));
	do
	{
		*tmpShort++ = (WCHAR_T)*tmpWChar++;
		++res;
	} while (len-- && *tmpWChar);

	return res;
}

// ----------------------------------------------------------------------------
const WCHAR_T* GetClassNames()
{
	static WCHAR_T* names = nullptr;
	if (!names)
	{
		::convToShortWchar(&names, L"NOPAPISolutions");
	}
	return names;
}

long GetClassObject
(
	const WCHAR_T* wsName,
	IComponentBase** pInterface
)
{
	if (!pInterface) return 0;
	*pInterface = new CNPUP_INCOMPENT_NATIVE();
	return 1;
}

long DestroyObject
(
	IComponentBase** pInterface
)
{
	if (!pInterface || !*pInterface) return 0;
	delete *pInterface;
	*pInterface = nullptr;
	return 1;
}

// ----------------------------------------------------------------------------

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::Init
(
	void *pInterface
)
{
	m_iConnect = (IAddInDefBaseEx*)pInterface;
	return m_iConnect != NULL;
}

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::setMemManager
(
	void * mem
)
{
	m_iMemory = (IMemoryManager*)mem;
	return m_iMemory != 0;
}

long ADDIN_API CNPUP_INCOMPENT_NATIVE::GetInfo()
{
	return 1000;
}

void ADDIN_API CNPUP_INCOMPENT_NATIVE::Done()
{
	if (cnpup_WndClass)
	{
		cnpup_WndClass->Wnd_Destroy();
		delete cnpup_WndClass;
		cnpup_WndClass = nullptr;
	}
	m_iConnect = nullptr;
	m_iMemory = nullptr;
}

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::RegisterExtensionAs
(
	WCHAR_T **wsExtensionName
)
{
	const wchar_t* wsExtension = NOPAPI_NAMEINCOMPENT;
	size_t iActualSize = ::wcslen(wsExtension) + 1;

	if (m_iMemory && wsExtensionName)
	{
		if (m_iMemory->AllocMemory((void**)wsExtensionName, static_cast<unsigned long>(iActualSize * sizeof(WCHAR_T))))
		{
			::wcscpy_s(*wsExtensionName, iActualSize, wsExtension);
			return true;
		}
	}
	return false;
}

long ADDIN_API CNPUP_INCOMPENT_NATIVE::GetNProps()
{
	return 0;
}

long ADDIN_API CNPUP_INCOMPENT_NATIVE::FindProp
(
	const WCHAR_T * wsPropName
)
{
	return 0;
}

const WCHAR_T *ADDIN_API CNPUP_INCOMPENT_NATIVE::GetPropName
(
	long lPropNum,
	long lPropAlias
)
{
	return 0;
}

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::GetPropVal
(
	const long lPropNum,
	tVariant * pvarPropVal
)
{
	return false;
}

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::SetPropVal
(
	const long lPropNum,
	tVariant * varPropVal
)
{
	return false;
}

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::IsPropReadable
(
	const long lPropNum
)
{
	return false;
}

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::IsPropWritable
(
	const long lPropNum
)
{
	return false;
}

long ADDIN_API CNPUP_INCOMPENT_NATIVE::GetNMethods()
{
	return (long)MICE_FINAL;
}

long ADDIN_API CNPUP_INCOMPENT_NATIVE::FindMethod
(
	const WCHAR_T * wsMethodName
)
{

	if (!wsMethodName) return -1;

	std::wstring_view method(wsMethodName);

#define MTHDL(id, en_name, ru_name, num_params) \
		if (method == en_name || method == ru_name) return id;
	METHOD_LIST
#undef MTHDL

		return -1;
}

const WCHAR_T* CNPUP_INCOMPENT_NATIVE::GetMethodName
(
	const long lMethodNum,
	const long lMethodAlias
)
{
	if (lMethodNum >= GetNMethods())
	{
		return NULL;
	}

	MethodsInCompEnt miceName = (MethodsInCompEnt)lMethodNum;
	const wchar_t *wsCurrentName = NULL;
	WCHAR_T *wsMethodName = NULL;

	int iActualSize = 0;

	switch (miceName)
	{
#define MTHDL(id, en_name, ru_name, num_params) \
		case id: \
			wsCurrentName = (lMethodAlias == 0) ? en_name : ru_name; \
			break;
		METHOD_LIST
#undef MTHDL
	default:
		wsCurrentName = L"";
		break;
	}

	iActualSize = wcslen(wsCurrentName) + 1;

	if (m_iMemory)
	{
		if (m_iMemory->AllocMemory((void**)&wsMethodName, iActualSize * sizeof(WCHAR_T)))
			::convToShortWchar(&wsMethodName, wsCurrentName, iActualSize);
	}
	return wsMethodName;
}

long ADDIN_API CNPUP_INCOMPENT_NATIVE::GetNParams
(
	const long lMethodNum
)
{
	MethodsInCompEnt miceName = (MethodsInCompEnt)lMethodNum;


	switch (lMethodNum)
	{
#define MTHDL(id, en_name, ru_name, num_params) \
		case id: return num_params;
		METHOD_LIST
#undef MTHDL
	default: return 0;
	}

	return 0;
}

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::GetParamDefValue
(
	const long lMethodNum,
	const long lParamNum,
	tVariant * pvarParamDefValue
)
{
	return false;
}

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::HasRetVal
(
	const long lMethodNum
)
{
	return false;
}

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::CallAsProc
(
	const long lMethodNum,
	tVariant * paParams,
	const long lSizeArray
)
{
	MethodsInCompEnt miceName = (MethodsInCompEnt)lMethodNum;

	if (!cnpup_WndClass
		&& miceName != MICE_DISTROY_WND)
	{
		cnpup_WndClass = new CNPUP_WindowClass();
	}

	if (miceName == MICE_CREATE_WND)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}

		cnpup_WndClass->Wnd_Create();

		return true;
	}
	else if (miceName == MICE_DISTROY_WND)
	{
		if (cnpup_WndClass)
		{
			cnpup_WndClass->Wnd_Destroy();
			delete cnpup_WndClass;
			cnpup_WndClass = nullptr;
		}
		return true;
	}
	else if (miceName == MICE_REDRAW_WND)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}

		cnpup_WndClass->Wnd_Redraw();

		return true;
	}
	// ----------------------------------------------------------------------------
	else if (miceName == MICE_SETCLR_BKGR)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];
		std::wstring clrBckgroundText;

		if (pParam.vt == VTYPE_PWSTR)
		{
			wchar_t* rawStr = pParam.pwstrVal;
			uint32_t strLen = pParam.wstrLen;

			if (cnpup_WndClass
				&& rawStr
				&& strLen > 0)
			{
				clrBckgroundText = std::wstring(rawStr, strLen);
			}
		}
		else if (pParam.vt == VTYPE_PSTR)
		{
			char* rawStr = pParam.pstrVal;
			uint32_t byteLen = pParam.strLen;

			if (cnpup_WndClass
				&& rawStr
				&& byteLen > 0)
			{
				int wlen = MultiByteToWideChar(CP_UTF8, 0, rawStr, byteLen, NULL, 0);
				if (wlen > 0)
				{
					std::wstring convertedStr(wlen, 0);
					MultiByteToWideChar(CP_UTF8, 0, rawStr, byteLen, &convertedStr[0], wlen);
					clrBckgroundText = std::wstring(convertedStr);
				}
			}
		}
		else
		{
			return false;
		}

		if (!clrBckgroundText.empty())
		{
			CharUpperBuffW(&clrBckgroundText[0], static_cast<DWORD>(clrBckgroundText.length()));

#define CLR(id, en_name, ru_name) \
			if (clrBckgroundText == en_name || clrBckgroundText == ru_name) \
			{ \
				cnpup_WndClass->SetColorElement_Background(id); \
				return true; \
			}
			COLOR_LIST
#undef CLR

				return false;

		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SETCLR_TEXT)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];
		std::wstring clrDrawText;

		if (pParam.vt == VTYPE_PWSTR)
		{
			wchar_t* rawStr = pParam.pwstrVal;
			uint32_t strLen = pParam.wstrLen;

			if (cnpup_WndClass
				&& rawStr
				&& strLen > 0)
			{
				clrDrawText = std::wstring(rawStr, strLen);
			}
		}
		else if (pParam.vt == VTYPE_PSTR)
		{
			char* rawStr = pParam.pstrVal;
			uint32_t byteLen = pParam.strLen;

			if (cnpup_WndClass
				&& rawStr
				&& byteLen > 0)
			{
				int wlen = MultiByteToWideChar(CP_UTF8, 0, rawStr, byteLen, NULL, 0);
				if (wlen > 0)
				{
					std::wstring convertedStr(wlen, 0);
					MultiByteToWideChar(CP_UTF8, 0, rawStr, byteLen, &convertedStr[0], wlen);
					clrDrawText = std::wstring(convertedStr);
				}
			}
		}
		else
		{
			return false;
		}

		if (!clrDrawText.empty())
		{
			CharUpperBuffW(&clrDrawText[0], static_cast<DWORD>(clrDrawText.length()));

#define CLR(id, en_name, ru_name) \
			if (clrDrawText == en_name || clrDrawText == ru_name) \
			{ \
				cnpup_WndClass->SetColorElement_Text(id); \
					return true; \
			}
			COLOR_LIST
#undef CLR
		}
		return false;
	}
	else if (miceName == MICE_SETCLR_BRDR)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];
		std::wstring clrBorder;

		if (pParam.vt == VTYPE_PWSTR)
		{
			wchar_t* rawStr = pParam.pwstrVal;
			uint32_t strLen = pParam.wstrLen;

			if (cnpup_WndClass
				&& rawStr
				&& strLen > 0)
			{
				clrBorder = std::wstring(rawStr, strLen);
			}
		}
		else if (pParam.vt == VTYPE_PSTR)
		{
			char* rawStr = pParam.pstrVal;
			uint32_t byteLen = pParam.strLen;

			if (cnpup_WndClass
				&& rawStr
				&& byteLen > 0)
			{
				int wlen = MultiByteToWideChar(CP_UTF8, 0, rawStr, byteLen, NULL, 0);
				if (wlen > 0)
				{
					std::wstring convertedStr(wlen, 0);
					MultiByteToWideChar(CP_UTF8, 0, rawStr, byteLen, &convertedStr[0], wlen);
					clrBorder = std::wstring(convertedStr);
				}
			}
		}
		else
		{
			return false;
		}

		if (!clrBorder.empty())
		{
			CharUpperBuffW(&clrBorder[0], static_cast<DWORD>(clrBorder.length()));

#define CLR(id, en_name, ru_name) \
			if (clrBorder == en_name || clrBorder == ru_name) \
			{ \
				cnpup_WndClass->SetColorElement_Border(id); \
				return true; \
			}
			COLOR_LIST
#undef CLR

				return false;

		}
		else
		{
			return false;
		}

		return true;
	}
	// ----------------------------------------------------------------------------
	else if (miceName == MICE_SET_TOPSIDE)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			if (rawBool)
			{
				cnpup_WndClass->SetTopSideWnd(true);
			}
			else
			{
				cnpup_WndClass->SetTopSideWnd(false);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SET_MODDRAW)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			if (rawBool)
			{
				cnpup_WndClass->SetModDrawWnd(true);
			}
			else
			{
				cnpup_WndClass->SetModDrawWnd(false);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SET_FIXPOS)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			if (rawBool)
			{
				cnpup_WndClass->SetFixPositionWnd(true);
			}
			else
			{
				cnpup_WndClass->SetFixPositionWnd(false);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SET_MULTISTR)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			if (rawBool)
			{
				cnpup_WndClass->SetMultistringDraw(true);
			}
			else
			{
				cnpup_WndClass->SetMultistringDraw(false);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SET_FIXSIZE)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			if (rawBool)
			{
				cnpup_WndClass->SetFixSizeWnd(true);
			}
			else
			{
				cnpup_WndClass->SetFixSizeWnd(false);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SET_DRAWBRDR)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			if (rawBool)
			{
				cnpup_WndClass->SetBorderDraw(true);
			}
			else
			{
				cnpup_WndClass->SetBorderDraw(false);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	// ----------------------------------------------------------------------------
	else if (miceName == MICE_SETFNT_USERFONT)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_PWSTR)
		{
			wchar_t* rawStr = pParam.pwstrVal;
			uint32_t strLen = pParam.wstrLen;

			if (cnpup_WndClass
				&& rawStr
				&& strLen > 0)
			{
				cnpup_WndClass->SetParamFont_Font(std::wstring(rawStr, strLen));
			}
		}
		else if (pParam.vt == VTYPE_PSTR)
		{
			char* rawStr = pParam.pstrVal;
			uint32_t byteLen = pParam.strLen;

			if (cnpup_WndClass
				&& rawStr
				&& byteLen > 0)
			{
				int wlen = MultiByteToWideChar(CP_UTF8, 0, rawStr, byteLen, NULL, 0);
				if (wlen > 0)
				{
					std::wstring convertedStr(wlen, 0);
					MultiByteToWideChar(CP_UTF8, 0, rawStr, byteLen, &convertedStr[0], wlen);
					cnpup_WndClass->SetParamFont_Font(convertedStr);
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SETFNT_ITALIC)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			if (rawBool)
			{
				cnpup_WndClass->SetParamFont_Italic(true);
			}
			else
			{
				cnpup_WndClass->SetParamFont_Italic(false);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SETFNT_UNDERLINE)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			if (rawBool)
			{
				cnpup_WndClass->SetParamFont_UnderLine(true);
			}
			else
			{
				cnpup_WndClass->SetParamFont_UnderLine(false);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SETFNT_STRIKELINE)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			if (rawBool)
			{
				cnpup_WndClass->SetParamFont_StrikeLine(true);
			}
			else
			{
				cnpup_WndClass->SetParamFont_StrikeLine(false);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SETFNT_BOLDFONT)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			if (rawBool)
			{
				cnpup_WndClass->SetParamFont_BoldFont(true);
			}
			else
			{
				cnpup_WndClass->SetParamFont_BoldFont(false);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else if (miceName == MICE_SET_AUTORDRW)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_BOOL)
		{
			bool rawBool = pParam.bVal;

			//if (rawBool)
			//{
			//	cnpup_WndClass->SetParamFont_BoldFont(true);
			//}
			//else
			//{
			//	cnpup_WndClass->SetParamFont_BoldFont(false);
			//}
		}
		else
		{
			return false;
		}

		return true;
	}

	// ----------------------------------------------------------------------------
	else if (miceName == MICE_SETSIZE_WINDOW)
	{
		int widhtSize = 0;
		int heighSize = 0;

		if (paParams[0].vt == VTYPE_I4
			&& paParams[1].vt == VTYPE_I4)
		{
			widhtSize = paParams[0].lVal;
			heighSize = paParams[1].lVal;
		}

		if (widhtSize > 0
			&& heighSize > 0)
		{
			cnpup_WndClass->SetSizeWindow(widhtSize, heighSize);
			return true;
		}
	}
	else if (miceName == MICE_SETSIZE_TEXT)
	{
		int fontSize = 0;

		if (paParams[0].vt == VTYPE_I4)
		{
			fontSize = paParams[0].lVal;
		}

		if (fontSize > 0)
		{
			cnpup_WndClass->SetSizeTextDraw(fontSize);
			return true;
		}
	}
	else if (miceName == MICE_SETSIZE_BORDER)
	{
		int borderSize = 0;

		if (paParams[0].vt == VTYPE_I4)
		{
			borderSize = paParams[0].lVal;
		}

		if (borderSize > 0)
		{
			cnpup_WndClass->SetSizeBorderDraw(borderSize);
			return true;
		}
	}
	// ----------------------------------------------------------------------------
	else if (miceName == MICE_SETDRAW_TEXT)
	{
		if (!cnpup_WndClass)
		{
			return false;
		}
		if (!paParams || lSizeArray < 1)
		{
			return false;
		}

		tVariant& pParam = paParams[0];

		if (pParam.vt == VTYPE_PWSTR)
		{
			wchar_t* rawStr = pParam.pwstrVal;
			uint32_t strLen = pParam.wstrLen;

			if (cnpup_WndClass
				&& rawStr
				&& strLen > 0)
			{
				cnpup_WndClass->SetTextDraw(std::wstring(rawStr, strLen));
			}
		}
		else if (pParam.vt == VTYPE_PSTR)
		{
			char* rawStr = pParam.pstrVal;
			uint32_t byteLen = pParam.strLen;

			if (cnpup_WndClass
				&& rawStr
				&& byteLen > 0)
			{
				int wlen = MultiByteToWideChar(CP_UTF8, 0, rawStr, byteLen, NULL, 0);
				if (wlen > 0)
				{
					std::wstring convertedStr(wlen, 0);
					MultiByteToWideChar(CP_UTF8, 0, rawStr, byteLen, &convertedStr[0], wlen);
					cnpup_WndClass->SetTextDraw(convertedStr);
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}


	return false;
}

bool ADDIN_API CNPUP_INCOMPENT_NATIVE::CallAsFunc
(
	const long lMethodNum,
	tVariant * pvarRetValue,
	tVariant * paParams,
	const long lSizeArray
)
{

	return false;
}

void ADDIN_API CNPUP_INCOMPENT_NATIVE::SetLocale
(
	const WCHAR_T * loc
)
{
	return;
}
