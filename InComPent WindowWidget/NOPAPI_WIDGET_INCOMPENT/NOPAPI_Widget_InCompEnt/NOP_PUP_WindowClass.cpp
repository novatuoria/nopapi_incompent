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



#include "pch.h"
#include "NOP_PUP_WindowClass.h"

#include <string>


HINSTANCE CNPUP_WindowClass::g_hInstance = NULL;



static LRESULT CALLBACK CNPUPGlobal_WndProc
(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	CNPUP_WindowClass* pThis = nullptr;

	if (message == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pThis = (CNPUP_WindowClass*)pCreate->lpCreateParams;
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
	}
	else
	{
		pThis = (CNPUP_WindowClass*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
	}

	if (pThis)
	{
		return pThis->WndProc(hWnd, message, wParam, lParam);
	}

	return DefWindowProcW(hWnd, message, wParam, lParam);
}

HMODULE GetCurrentModule()
{
	HMODULE hModule = NULL;

	GetModuleHandleEx
	(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
		| GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		(LPCTSTR)GetCurrentModule,
		&hModule
	);

	return hModule;
}



COLORREF CNPUP_WindowClass::ReturnColorElement
(
	ColorElementWnd clrElem
)
{
	COLORREF clrReturn = RGB(0, 128, 128);

	if (clrElem == CEW_BLACK)
	{
		clrReturn = RGB(0, 0, 0);
	}
	else if (clrElem == CEW_RED)
	{
		clrReturn = RGB(255, 0, 0);
	}
	else if (clrElem == CEW_ORANGE)
	{
		clrReturn = RGB(255, 128, 0);
	}
	else if (clrElem == CEW_YELLOW)
	{
		clrReturn = RGB(255, 255, 0);
	}
	else if (clrElem == CEW_GREEN)
	{
		clrReturn = RGB(0, 255, 0);
	}
	else if (clrElem == CEW_BLUE)
	{
		clrReturn = RGB(0, 0, 255);
	}
	else if (clrElem == CEW_VIOLET)
	{
		clrReturn = RGB(128, 0, 255);
	}
	else if (clrElem == CEW_INDIGO)
	{
		clrReturn = RGB(255, 0, 128);
	}
	else if (clrElem == CEW_MAGENTA)
	{
		clrReturn = RGB(255, 0, 255);
	}
	else if (clrElem == CEW_WHITE)
	{
		clrReturn = RGB(255, 255, 255);
	}
	else
	{
		clrReturn = RGB(0, 128, 128);
	}

	return clrReturn;
}



void CNPUP_WindowClass::InitialWindow()
{
	if (!g_hInstance)
	{
		g_hInstance = (HINSTANCE)GetCurrentModule();
	}

	WNDCLASSEXW wcex{};
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.style = CS_DBLCLKS /*CS_HREDRAW | CS_VREDRAW*/;
	wcex.lpfnWndProc = CNPUPGlobal_WndProc;
	wcex.hInstance = g_hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszClassName = m_RegisterClassName.c_str();

	RegisterClassExW(&wcex);

	DWORD dwExStyle;

	if (m_bTopSide)
	{
		dwExStyle = WS_EX_LAYERED | WS_EX_TOPMOST;
	}
	else
	{
		dwExStyle = WS_EX_LAYERED;
	}

	m_hWnd = CreateWindowExW
	(
		dwExStyle,
		m_RegisterClassName.c_str(), L"NOP PUP InCompEnt: WindowWidget",
		WS_POPUP,
		0, 0, m_iSizeWnd_Width, m_iSizeWnd_Heigh,
		NULL, NULL, g_hInstance, this
	);
	SetWindowLong
	(
		m_hWnd, GWL_EXSTYLE,
		GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED
	);

	SetLayeredWindowAttributes
	(
		m_hWnd, NULL, 0, LWA_COLORKEY
	);

	if (!m_hWnd) return;

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	UpdateWidget();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnregisterClassW(m_RegisterClassName.c_str(), g_hInstance);
}

void CNPUP_WindowClass::UpdateWidget()
{
	if (!m_hWnd)
	{
		return;
	}

	CreateFontTextDraw();

	HDC hdc = GetDC(m_hWnd);
	HFONT hOldFont = (HFONT)SelectObject(hdc, m_hFont);

	int newWidth = 0;
	int newHeight = 0;

	if (m_bMultiStringDraw)
	{
		int marginX = 8;
		int marginY = 8;
		if (!m_bWndDraw && m_bSizeWnd)
		{
			marginX = 0;
			marginY = 0;
		}

		RECT calcRect = { 0, 0, 0, 0 };

		if (m_bSizeWnd)
		{
			newWidth = m_iSizeWnd_Width;
			newHeight = m_iSizeWnd_Heigh;
		}
		else
		{
			DrawTextW(hdc, m_TextDraw.c_str(), -1, &calcRect, DT_EDITCONTROL | DT_CALCRECT);
			newWidth = (calcRect.right - calcRect.left);
			newHeight = (calcRect.bottom - calcRect.top);
		}
	}
	else
	{
		SIZE textSize;
		GetTextExtentPoint32W(hdc, m_TextDraw.c_str(), m_TextDraw.length(), &textSize);

		if (!m_bSizeWnd)
		{
			newWidth = textSize.cx;
			newHeight = textSize.cy;
		}
		else
		{
			newWidth = m_iSizeWnd_Width;
			newHeight = m_iSizeWnd_Heigh;
		}
	}

	UINT uFormatOutText;
	if (m_bMultiStringDraw)
	{
		uFormatOutText = DT_WORDBREAK | DT_EDITCONTROL;
	}
	else
	{
		uFormatOutText = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
	}

	SelectObject(hdc, hOldFont);
	ReleaseDC(m_hWnd, hdc);
	HWND hWndInsertAfter = m_bTopSide ? HWND_TOPMOST : HWND_NOTOPMOST;
	SetWindowPos(m_hWnd, hWndInsertAfter, 0, 0, newWidth, newHeight,
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOREDRAW | SWP_FRAMECHANGED);

	hdc = GetDC(m_hWnd);
	hOldFont = (HFONT)SelectObject(hdc, m_hFont);

	if (m_bWndDraw)
	{
		RECT rectClient = { 0, 0, newWidth, newHeight };

		int oldBkMode = SetBkMode(hdc, TRANSPARENT);

		BeginPath(hdc);
		DrawTextW(
			hdc, m_TextDraw.c_str(), -1,
			&rectClient,
			uFormatOutText
		);
		EndPath(hdc);

		if (oldBkMode) SetBkMode(hdc, oldBkMode);

		HRGN hLettersRgn = PathToRegion(hdc);

		if (hLettersRgn)
		{
			if (!SetWindowRgn(m_hWnd, hLettersRgn, TRUE))
			{
				DeleteObject(hLettersRgn);
			}
		}

	}
	else
	{
		RECT rectClient = { 0, 0, newWidth, newHeight };
		HRGN hInvertedRgn = CreateRectRgnIndirect(&rectClient);

		if (!SetWindowRgn(m_hWnd, hInvertedRgn, TRUE))
		{
			DeleteObject(hInvertedRgn);
		}
	}

	SelectObject(hdc, hOldFont);
	ReleaseDC(m_hWnd, hdc);

	SetLayeredWindowAttributes(m_hWnd, NULL, 255, LWA_ALPHA);

	InvalidateRect(m_hWnd, NULL, FALSE);

}

void CNPUP_WindowClass::CreateFontTextDraw()
{
	if (m_hFont)
	{
		return;
	}

	int iBoldFont = 0;

	if (m_bBoldFontDraw)
	{
		iBoldFont = FW_BOLD;
	}
	else
	{
		iBoldFont = FW_NORMAL;
	}

	m_hFont = CreateFontW(
		m_iSizeTextDraw, 0, 0, 0,
		iBoldFont,
		m_bItalicFont, m_bUnderlineFont, m_bStrikeOutFont,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH | FF_DONTCARE,
		m_NameFontTextDraw.c_str());

}



CNPUP_WindowClass::CNPUP_WindowClass()
{
	// Major.Minor.Patch

	m_TextDraw = LR"(>>> | NOP PUP InCompEnt: WindowWidget | <<<
	= Версия: 1.1 Junior                      =
	=  Автор: Михайлова Александра Андреевна  =
	                2026 год :)
	 -----------------------------------------
	[         Ожидание данных от 1С...        ])";
	m_NameFontTextDraw = L"Courier New";
	m_RegisterClassName = L"CNPUP_WinWid";

	m_clrBakcground = CEW_BLACK;
	m_clrText = CEW_RED;
	m_clrBorder = CEW_BLUE;

	m_hWnd = NULL;
	m_hFont = NULL;

	m_iSizeWnd_Heigh = 250;
	m_iSizeWnd_Width = 500;
	m_iSizeTextDraw = 20;
	m_iSizeBorder = 2;
	m_iAlpha = 255;

	m_bAutoDraw = false;
	m_bTopSide = false;
	m_bFixedPos = false;
	m_bWndDraw = false;
	m_bSizeWnd = false;
	m_bDrawBorder = false;
	m_bMultiStringDraw = true;
	m_bBoldFontDraw = true;
	m_bItalicFont = false;
	m_bUnderlineFont = false;
	m_bStrikeOutFont = false;

	CreateFontTextDraw();

}


LRESULT CNPUP_WindowClass::WndProc
(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{

	switch (message)
	{
	case WM_NCHITTEST:
	{
		if (m_bFixedPos)
		{
			return FALSE;
		}
		else
		{
			LRESULT hit = DefWindowProc(hWnd, message, wParam, lParam);

			if (hit == HTCLIENT)
			{
				return HTCAPTION;
			}
			return hit;
		}
	}
	case WM_ERASEBKGND:
	{
		return TRUE;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		RECT rectClient;
		GetClientRect(hWnd, &rectClient);
		int width = rectClient.right - rectClient.left;
		int height = rectClient.bottom - rectClient.top;

		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBitmap = CreateCompatibleBitmap(hdc, width, height);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

		HBRUSH hBtnFace = CreateSolidBrush(ReturnColorElement(m_clrBakcground));
		FillRect(memDC, &rectClient, hBtnFace);
		DeleteObject(hBtnFace);

		HFONT hOldFont = (HFONT)SelectObject(memDC, m_hFont);

		if (m_bWndDraw)
		{
			HBRUSH hTextBrush = CreateSolidBrush(ReturnColorElement(m_clrText));
			FillRect(memDC, &rectClient, hTextBrush);
			DeleteObject(hTextBrush);
		}
		else
		{
			COLORREF oldTextColor = SetTextColor(memDC, ReturnColorElement(m_clrText));
			COLORREF oldBkColor = SetBkColor(memDC, ReturnColorElement(m_clrBakcground));

			UINT uFormatOutText;
			if (m_bMultiStringDraw)
			{
				uFormatOutText = DT_WORDBREAK | DT_EDITCONTROL;
			}
			else
			{
				uFormatOutText = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
			}

			DrawTextW(memDC, m_TextDraw.c_str(), -1, &rectClient, uFormatOutText);

			SetBkColor(memDC, oldBkColor);
			SetTextColor(memDC, oldTextColor);
		}

		if (m_bDrawBorder)
		{
			RECT rectBorder;
			rectBorder.left = m_iSizeBorder;
			rectBorder.top = m_iSizeBorder;
			rectBorder.right = width - m_iSizeBorder;
			rectBorder.bottom = height - m_iSizeBorder;

			HRGN rgnClient = CreateRectRgnIndirect(&rectClient);
			HRGN rgnInvert = CreateRectRgnIndirect(&rectBorder);
			HRGN rgnFinal = CreateRectRgn(0, 0, 0, 0);

			CombineRgn(rgnFinal, rgnClient, rgnInvert, RGN_DIFF);

			HBRUSH hBorder = CreateSolidBrush(ReturnColorElement(m_clrBorder));
			FillRgn(memDC, rgnFinal, hBorder);

			DeleteObject(hBorder);
			DeleteObject(rgnClient);
			DeleteObject(rgnInvert);
			DeleteObject(rgnFinal);
		}

		SelectObject(memDC, hOldFont);

		BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

		SelectObject(memDC, oldBitmap);
		DeleteObject(memBitmap);
		DeleteDC(memDC);

		EndPaint(hWnd, &ps);
		return TRUE;
	}
	case UM_NOPAPI_SYS_WNDRDRW:
	{
		UpdateWidget();

		return TRUE;
	}
	case UM_NOPAPI_SET_TEXT:
	{
		std::wstring* pReceivedText = (std::wstring*)lParam;

		if (pReceivedText)
		{
			if (*pReceivedText != m_TextDraw)
			{
				m_TextDraw = *pReceivedText;
				delete pReceivedText;

				if (m_bAutoDraw)
				{
					UpdateWidget();
				}
			}

			delete pReceivedText;

		}

		return TRUE;
	}
	case UM_NOPAPI_SET_MOVPOS:
	{
		if (m_bFixedPos != (bool)lParam)
		{
			m_bFixedPos = (bool)lParam;

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SET_AUTODRAWE:
	{
		if (m_bAutoDraw != (bool)lParam)
		{
			m_bAutoDraw = (bool)lParam;
		}

		return TRUE;
	}
	case UM_NOPAPI_SET_TOPSIDE:
	{
		if (m_bTopSide != (bool)lParam)
		{
			m_bTopSide = (bool)lParam;

			LONG_PTR exStyle = GetWindowLongPtrW(m_hWnd, GWL_EXSTYLE);

			if (m_bTopSide)
			{
				exStyle |= WS_EX_TOPMOST;
			}
			else
			{
				exStyle &= ~WS_EX_TOPMOST;
			}

			SetWindowLongPtrW(m_hWnd, GWL_EXSTYLE, exStyle);

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}

		}

		return TRUE;
	}
	case UM_NOPAPI_SET_MODDRIVE:
	{
		if (m_bWndDraw != (bool)lParam)
		{
			m_bWndDraw = (bool)lParam;

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SET_FIXSIZE:
	{
		if (m_bSizeWnd != (bool)lParam)
		{
			m_bSizeWnd = (bool)lParam;

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SET_BORDER:
	{
		if (m_bDrawBorder != (bool)lParam)
		{
			m_bDrawBorder = (bool)lParam;

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SET_MULTISTR:
	{
		if (m_bMultiStringDraw != (bool)lParam)
		{
			m_bMultiStringDraw = (bool)lParam;

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETCLR_TEXT:
	{
		if (m_clrText != (ColorElementWnd)lParam)
		{
			m_clrText = (ColorElementWnd)lParam;

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETCLR_BCKG:
	{
		if (m_clrBakcground != (ColorElementWnd)lParam)
		{
			m_clrBakcground = (ColorElementWnd)lParam;

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETCLR_BRDR:
	{
		if (m_clrBorder != (ColorElementWnd)lParam)
		{
			m_clrBorder = (ColorElementWnd)lParam;

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETSIZE_TEXT:
	{
		if ((int)lParam > 0
			&& m_iSizeTextDraw != (int)lParam)
		{
			if (m_hFont)
			{
				DeleteObject(m_hFont);
				m_hFont = NULL;
			}

			m_iSizeTextDraw = (int)lParam;

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETSIZE_WIND:
	{
		if ((__int64)lParam > 0)
		{
			bool bIsResize = false;

			__int64 packedResult = (__int64)lParam;
			int iSizeWidht = (int)(packedResult >> 32);
			int iSizeHeigh = (int)packedResult;

			if (iSizeWidht != m_iSizeWnd_Width)
			{
				m_iSizeWnd_Width = iSizeWidht;

				bIsResize = true;
			}
			if (iSizeHeigh != m_iSizeWnd_Heigh)
			{
				m_iSizeWnd_Heigh = iSizeHeigh;

				bIsResize = true;
			}

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETSIZE_BRDR:
	{
		if ((int)lParam > 0
			&& m_iSizeBorder != (int)lParam)
		{
			m_iSizeBorder = (int)lParam;

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETFNT_ITALC:
	{
		if (m_bItalicFont != (bool)lParam)
		{
			m_bItalicFont = (bool)lParam;

			if (m_hFont)
			{
				DeleteObject(m_hFont);
				m_hFont = NULL;
			}

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETFNT_UNDLN:
	{
		if (m_bUnderlineFont != (bool)lParam)
		{
			m_bUnderlineFont = (bool)lParam;

			if (m_hFont)
			{
				DeleteObject(m_hFont);
				m_hFont = NULL;
			}

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETFNT_STRLN:
	{
		if (m_bStrikeOutFont != (bool)lParam)
		{
			m_bStrikeOutFont = (bool)lParam;

			if (m_hFont)
			{
				DeleteObject(m_hFont);
				m_hFont = NULL;
			}

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETFNT_BLFNT:
	{
		if (m_bBoldFontDraw != (bool)lParam)
		{
			m_bBoldFontDraw = (bool)lParam;

			if (m_hFont)
			{
				DeleteObject(m_hFont);
				m_hFont = NULL;
			}

			if (m_bAutoDraw)
			{
				UpdateWidget();
			}
		}

		return TRUE;
	}
	case UM_NOPAPI_SETFNT_UFONT:
	{
		std::wstring* pReceivedText = (std::wstring*)lParam;

		if (pReceivedText)
		{
			if (*pReceivedText != m_NameFontTextDraw)
			{
				m_NameFontTextDraw = *pReceivedText;
				delete pReceivedText;

				if (m_hFont)
				{
					DeleteObject(m_hFont);
					m_hFont = NULL;
				}

				if (m_bAutoDraw)
				{
					UpdateWidget();
				}
			}

			delete pReceivedText;

		}

		return TRUE;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



void CNPUP_WindowClass::Wnd_Create()
{
	if (m_windowThread.joinable())
	{
		return;
	}
	m_windowThread = std::thread(&CNPUP_WindowClass::InitialWindow, this);
}

void CNPUP_WindowClass::Wnd_Destroy()
{
	if (m_hWnd && IsWindow(m_hWnd))
	{
		PostMessage(m_hWnd, WM_CLOSE, 0, 0);
	}

	if (m_windowThread.joinable())
	{
		m_windowThread.join();
	}

	m_hWnd = nullptr;
}

void CNPUP_WindowClass::Wnd_Redraw()
{
	if (!m_hWnd)
	{
		return;
	}

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SYS_WNDRDRW, 0, NULL))
	{
		return;
	}
}




void CNPUP_WindowClass::SetColorElement_Text
(
	ColorElementWnd clrText
)
{
	if (!m_hWnd)
	{
		return;
	}

	ColorElementWnd clrSet = clrText;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SETCLR_TEXT, 0, (LPARAM)clrSet))
	{

		return;
	}

}

void CNPUP_WindowClass::SetColorElement_Background
(
	ColorElementWnd clrBackground
)
{
	if (!m_hWnd)
	{
		return;
	}

	ColorElementWnd clrSet = clrBackground;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SETCLR_BCKG, 0, (LPARAM)clrSet))
	{
		return;
	}

}

void CNPUP_WindowClass::SetColorElement_Border(ColorElementWnd clrBorder)
{
	if (!m_hWnd)
	{
		return;
	}

	ColorElementWnd clrSet = clrBorder;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SETCLR_BRDR, 0, (LPARAM)clrSet))
	{
		return;
	}
}



void CNPUP_WindowClass::SetModDrawWnd
(
	bool bModDraw
)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bModDraw;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SET_MODDRIVE, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}

void CNPUP_WindowClass::SetFixPositionWnd
(
	bool bFixPos
)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bFixPos;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SET_MOVPOS, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}

void CNPUP_WindowClass::SetTopSideWnd
(
	bool bTopSide
)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bTopSide;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SET_TOPSIDE, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}

void CNPUP_WindowClass::SetMultistringDraw(bool bMultiDraw)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bMultiDraw;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SET_MULTISTR, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}

void CNPUP_WindowClass::SetFixSizeWnd(bool bFixSize)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bFixSize;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SET_FIXSIZE, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}

void CNPUP_WindowClass::SetBorderDraw(bool bBorder)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bBorder;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SET_BORDER, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}

void CNPUP_WindowClass::SetAutoRedraw(bool bAuto)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bAuto;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SET_AUTODRAWE, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}

void CNPUP_WindowClass::SetParamFont_Italic(bool bParamFont)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bParamFont;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SETFNT_ITALC, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}

void CNPUP_WindowClass::SetParamFont_UnderLine(bool bParamFont)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bParamFont;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SETFNT_UNDLN, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}

void CNPUP_WindowClass::SetParamFont_StrikeLine(bool bParamFont)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bParamFont;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SETFNT_STRLN, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}

void CNPUP_WindowClass::SetParamFont_BoldFont(bool bParamFont)
{
	if (!m_hWnd)
	{
		return;
	}

	bool bMsgBool = bParamFont;

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SETFNT_BLFNT, 0, (LPARAM)bMsgBool))
	{
		return;
	}
}


void CNPUP_WindowClass::SetSizeWindow(int iSizeWidht, int iSizeHeigh)
{
	if (!m_hWnd)
	{
		return;
	}

	if (iSizeWidht > 0
		&& iSizeHeigh > 0)
	{
		__int64 packedResult = ((__int64)iSizeWidht << 32) | (unsigned int)iSizeHeigh;

		if (!PostMessageW(m_hWnd, UM_NOPAPI_SETSIZE_WIND, 0, (LPARAM)packedResult))
		{
			return;
		}
	}

	return;

}

void CNPUP_WindowClass::SetSizeTextDraw(int iSizeText)
{
	if (!m_hWnd)
	{
		return;
	}

	if (iSizeText > 0)
	{
		if (!PostMessageW(m_hWnd, UM_NOPAPI_SETSIZE_TEXT, 0, (LPARAM)iSizeText))
		{
			return;
		}
	}

}

void CNPUP_WindowClass::SetSizeBorderDraw(int iSizeBorder)
{
	if (!m_hWnd)
	{
		return;
	}

	if (iSizeBorder > 0)
	{
		if (!PostMessageW(m_hWnd, UM_NOPAPI_SETSIZE_BRDR, 0, (LPARAM)iSizeBorder))
		{
			return;
		}
	}

}

void CNPUP_WindowClass::SetPositionWindow(int iPosWnd_X, int iPosWnd_Y)
{


}

void CNPUP_WindowClass::SetAlphaChanelWindow(int iAlpha)
{
	if (!m_hWnd)
	{
		return;
	}

}

void CNPUP_WindowClass::SetParamFont_Font
(
	std::wstring bParamFont
)
{
	if (!m_hWnd)
	{
		return;
	}

	std::wstring* pTextCopy = new std::wstring(bParamFont);

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SETFNT_UFONT, 0, (LPARAM)pTextCopy))
	{
		delete pTextCopy;
	}

}

void CNPUP_WindowClass::SetTextDraw
(
	std::wstring textDraw
)
{
	if (!m_hWnd)
	{
		return;
	}

	std::wstring* pTextCopy = new std::wstring(textDraw);

	if (!PostMessageW(m_hWnd, UM_NOPAPI_SET_TEXT, 0, (LPARAM)pTextCopy))
	{
		delete pTextCopy;
	}
}

