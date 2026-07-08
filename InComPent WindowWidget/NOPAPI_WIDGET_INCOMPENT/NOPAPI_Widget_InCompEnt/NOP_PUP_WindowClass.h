// =====================  NOVATUORIA   ORIGINAL   PROJECT  ====================
//                                                                             
//
//               #/1| /7  #/==/7  #/==/7    #/==/7  #/  /7  #/==/7
//              #/ |1//  #/  //  #/==//    #/==//  #/  //  #/==//
//             #/  |//  #/==//  #/        #/      #/==//  #/
//
//
//              Novatuoria Project API Solutions - Window Class
//
//         Проект: NOP PUP InCompEnt "WindowWidget" 
//         Версия: ver. 1.0 "Junior"
//          Автор: Александра (@novatuoria)
//         GitHub: https://github.com/novatuoria
//    Репозиторий: https://github.com/novatuoria/nopapi_incompent
//        License: MIT
//
//
//                                   2026
//
// ===================== PROPER   UNIVERSAL   PERFORMANCES ====================



#pragma once
#include <windows.h>
#include <thread>


// ---------------------   USER MESSAGE NOPAPI WIN32 API   --------------------
#pragma region UserMessage

#define UM_NOPAPI_SYS_WNDRDRW					(WM_USER + 0x4401) //

#define UM_NOPAPI_SET_MOVPOS					(WM_USER + 0x72A1) //
#define UM_NOPAPI_SET_TEXT						(WM_USER + 0x32A2) //
#define UM_NOPAPI_SET_TOPSIDE					(WM_USER + 0x42A3) //
#define UM_NOPAPI_SET_MODDRIVE					(WM_USER + 0x52A4) //
#define UM_NOPAPI_SET_FIXSIZE					(WM_USER + 0x62A5) //
#define UM_NOPAPI_SET_BORDER					(WM_USER + 0x22A6) //
#define UM_NOPAPI_SET_MULTISTR					(WM_USER + 0x12A7) //
#define UM_NOPAPI_SET_AUTODRAWE					(WM_USER + 0x82A8) //

#define UM_NOPAPI_SETCLR_TEXT					(WM_USER + 0x00B1) //
#define UM_NOPAPI_SETCLR_BCKG					(WM_USER + 0x00B2) //
#define UM_NOPAPI_SETCLR_BRDR					(WM_USER + 0x00B3) //

#define UM_NOPAPI_SETUSERCLR_TEXT				(WM_USER + 0x00C1) /*notrelise*/
#define UM_NOPAPI_SETUSERCLR_BCKG				(WM_USER + 0x00C2) /*notrelise*/
#define UM_NOPAPI_SETUSERCLR_BRDR				(WM_USER + 0x00C3) /*notrelise*/

#define UM_NOPAPI_SETSIZE_TEXT					(WM_USER + 0x1001) //
#define UM_NOPAPI_SETSIZE_WIND					(WM_USER + 0x1002) //
#define UM_NOPAPI_SETSIZE_BRDR					(WM_USER + 0x1003) //

#define UM_NOPAPI_SETVAL_ALPHA					(WM_USER + 0x2001) /*notrelise*/
#define UM_NOPAPI_SETVAL_POSWND					(WM_USER + 0x2002) /*notrelise*/

#define UM_NOPAPI_SETFNT_ITALC					(WM_USER + 0x00A1) //
#define UM_NOPAPI_SETFNT_UNDLN					(WM_USER + 0x00A2) //
#define UM_NOPAPI_SETFNT_STRLN					(WM_USER + 0x00A3) //
#define UM_NOPAPI_SETFNT_UFONT					(WM_USER + 0x00A4) //
#define UM_NOPAPI_SETFNT_BLFNT					(WM_USER + 0x00A5) //

#pragma endregion
// ----------------------------------------------------------------------------



class CNPUP_WindowClass
{
private:
	static HINSTANCE g_hInstance;
public:
	enum ColorElementWnd
	{
		CEW_BLACK,

		CEW_RED,
		CEW_ORANGE,
		CEW_YELLOW,
		CEW_GREEN,
		CEW_BLUE,
		CEW_VIOLET,
		CEW_INDIGO,
		CEW_MAGENTA,

		CEW_WHITE
	};

private:
	HWND m_hWnd;
	HFONT m_hFont;

	COLORREF m_clrUser_Background;
	COLORREF m_clrUser_Border;
	COLORREF m_clrUser_Text;

	ColorElementWnd m_clrBakcground;
	ColorElementWnd m_clrBorder;
	ColorElementWnd m_clrText;

	std::thread m_windowThread;

	std::wstring m_TextDraw;
	std::wstring m_NameFontTextDraw;
	std::wstring m_RegisterClassName;
	
	int m_iSizeWnd_Heigh;
	int m_iSizeWnd_Width;
	int m_iSizeTextDraw;
	int m_iSizeBorder;

	int m_iPosWnd_XWnd;
	int m_iPosWnd_YWnd;

	int m_iAlpha;

	bool m_bAutoDraw;
	bool m_bTopSide; //поверх всех окон
	bool m_bFixedPos; //фиксировать положение
	bool m_bWndDraw; //рисовать фон окна
	bool m_bSizeWnd; //устанавливать размер окна (false - обрезает автоматом, true - размер задается пользователем)
	bool m_bDrawBorder; //рисовать границу окна
	bool m_bMultiStringDraw; //многострочный режим текста

	bool m_bBoldFontDraw; //жирный шрифт
	bool m_bItalicFont; //курсив
	bool m_bUnderlineFont; //подчеркнутый
	bool m_bStrikeOutFont; //зачеркнутый

private:
	COLORREF ReturnColorElement(ColorElementWnd clrElem);

	void InitialWindow();
	void UpdateWidget();
	void CreateFontTextDraw();

public:

	CNPUP_WindowClass();

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Wnd_Create();
	void Wnd_Destroy();
	void Wnd_Redraw();


	// SET PARAM CLASS
	void SetColorElement_Text(ColorElementWnd clrText);
	void SetColorElement_Background(ColorElementWnd clrBackground);
	void SetColorElement_Border(ColorElementWnd clrBorder);

	void SetModDrawWnd(bool bModDraw);
	void SetFixPositionWnd(bool bFixPos);
	void SetTopSideWnd(bool bTopSide);
	void SetMultistringDraw(bool bMultiDraw);
	void SetFixSizeWnd(bool bFixSize);
	void SetBorderDraw(bool bBorder);
	void SetAutoRedraw(bool bAuto);

	void SetParamFont_Italic(bool bParamFont);
	void SetParamFont_UnderLine(bool bParamFont);
	void SetParamFont_StrikeLine(bool bParamFont);
	void SetParamFont_BoldFont(bool bParamFont);
	void SetParamFont_Font(std::wstring bParamFont);

	void SetSizeWindow(int iSizeWidht, int iSizeHeigh);
	void SetSizeTextDraw(int iSizeText);
	void SetSizeBorderDraw(int iSizeBorder);

	void SetPositionWindow(int iPosWnd_X, int iPosWnd_Y);
	void SetAlphaChanelWindow(int iAlpha);
	void SetTextDraw(std::wstring textDraw);

};