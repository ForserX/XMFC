#include "pch.h"
#include "Static.h"

BEGIN_MESSAGE_MAP(XStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void XStatic::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
	LPCTSTR lpszText = (LPCTSTR)lpDrawItemStruct->itemData;
	ASSERT(lpszText != NULL);
	CDC dc;

	dc.Attach(lpDrawItemStruct->hDC);

	// If this item is selected, set the background color
	// and the text color to appropriate values. Erase
	// the rect by filling it with the background color.
	if (bCaption)
	{
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, RGB(21, 21, 21));
	}
	else
	{
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, GetGlobalData()->clrWindow);
	}
	dc.SetTextColor(GetGlobalData()->clrWindowText);
	// If drawing selected, add the pushed style to DrawFrameControl.

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, GetGlobalData()->clrActiveBorder);
	}

	// Draw the text.
	CString Text;
	CRect TextRect = lpDrawItemStruct->rcItem;
	TextRect.left += 5;

	GetWindowText(Text);
	dc.DrawText(Text, (int)_tcslen(Text), &TextRect, DT_LEFT | DT_SINGLELINE);

	dc.Detach();
}

BOOL XStatic::Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	dwStyle |= SS_OWNERDRAW;
	return CStatic::Create(lpszText, dwStyle, rect, pParentWnd, nID);
}

void XStatic::SetMode(bool Mode, bool Frame)
{
	bCaption = Mode;
	bFrame = Frame;
}

void XStatic::OnPaint()
{
	CStatic::OnPaint();

	CDC* DC = GetDC();

	CRect Rect;
	GetClientRect(Rect);

	if (bFrame)
	{
		CPen Pen(PS_SOLID, 1, RGB(0, 0, 0));
		DC->SelectObject(&Pen);

		DC->MoveTo(Rect.left, Rect.top);
		DC->LineTo(Rect.left, Rect.bottom);
		DC->LineTo(Rect.right, Rect.bottom);
		DC->LineTo(Rect.right, Rect.top);
		DC->LineTo(Rect.left, Rect.top);
	}

	ReleaseDC(DC);
}