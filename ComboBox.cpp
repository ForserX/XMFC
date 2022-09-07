#include "pch.h"
#include "ComboBox.h"

BEGIN_MESSAGE_MAP(XComboBox, CComboBox)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void XComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
    LPCTSTR lpszText = (LPCTSTR)lpDrawItemStruct->itemData;
    ASSERT(lpszText != NULL);
    CDC dc;

    dc.Attach(lpDrawItemStruct->hDC);
    dc.FillSolidRect(&lpDrawItemStruct->rcItem, GetGlobalData()->clrWindow);

    // If this item is selected, set the background color
    // and the text color to appropriate values. Erase
    // the rect by filling it with the background color.
    if (lpDrawItemStruct->itemState & ODS_SELECTED)
    {
        dc.FillSolidRect(&lpDrawItemStruct->rcItem, GetGlobalData()->clrWindowFrame);
    }

    dc.SetTextColor(GetGlobalData()->clrWindowText);

    if (GetCount() > 0)
    {
        CRect TextRect = lpDrawItemStruct->rcItem;
        TextRect.left += 5;
        // Draw the text.
        dc.DrawText(lpszText, (int)_tcslen(lpszText), &TextRect, DT_VCENTER | DT_SINGLELINE);
    }

    dc.Detach();
}

XComboBox::XComboBox() : CComboBox()
{
}

HBRUSH XComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    return GetGlobalData()->brWindow;
}

BOOL XComboBox::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
    // For DrawItem call
    dwStyle |= CBS_OWNERDRAWVARIABLE;
    
    bool bResult = CComboBox::Create(dwStyle, rect, pParentWnd, nID);
    ModifyStyle(WS_BORDER, 0);

    return bResult;
}
