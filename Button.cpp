#include "pch.h"
#include "Button.h"

void XButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// This code only works with buttons.
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	dc.FillSolidRect(&lpDrawItemStruct->rcItem, GetGlobalData()->clrWindow);

	// If drawing selected, add the pushed style to DrawFrameControl.
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, GetGlobalData()->clrActiveBorder);
	}

	// Get the button's text.
	CString strText;
	GetWindowText(strText);

	// Draw the button text using the text color red.
	COLORREF cColor = ::SetTextColor(lpDrawItemStruct->hDC, GetGlobalData()->clrWindowText);
	::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(),
		&lpDrawItemStruct->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	::SetTextColor(lpDrawItemStruct->hDC, cColor);

	CRect rect = &lpDrawItemStruct->rcItem;

	CPen pen(PS_SOLID, 1, GetGlobalData()->clrWindowFrame);
	dc.SelectObject(pen);
	
	dc.MoveTo(CPoint(rect.left +1, rect.bottom -1));
	dc.LineTo(CPoint(rect.right -1, rect.bottom -1));	
	dc.LineTo(CPoint(rect.right -1, rect.top+1));
	dc.LineTo(CPoint(rect.left+1, rect.top+1));
	dc.LineTo(CPoint(rect.left+1, rect.bottom -1));

	dc.Detach();
}

BOOL XButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	dwStyle |= BS_OWNERDRAW;
	return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
}