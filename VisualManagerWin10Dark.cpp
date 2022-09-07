#include "pch.h"
#include "resource.h"
#include "VisualManagerWin10Dark.h"

using namespace Gdiplus;

float GetScaleFactorFromEnum(DEVICE_SCALE_FACTOR ScaleFactor)
{
    switch (ScaleFactor)
    {
    case SCALE_120_PERCENT:
        return 1.2f;
	case SCALE_125_PERCENT:
        return 1.25f;
	case SCALE_140_PERCENT:
        return 1.4f;
	case SCALE_150_PERCENT:
        return 1.5f;
	case SCALE_160_PERCENT:
        return 1.6f;
	case SCALE_175_PERCENT:
        return 1.75f;
	case SCALE_180_PERCENT:
        return 1.8f;
	case SCALE_200_PERCENT:
        return 2.0f;
	case SCALE_225_PERCENT:
		return 2.25f;
	case SCALE_250_PERCENT:
		return 2.5f;
	case SCALE_300_PERCENT:
		return 3.0f;
	case SCALE_350_PERCENT:
		return 3.5f;
	case SCALE_400_PERCENT:
		return 4.0f;
	case SCALE_450_PERCENT:
		return 4.5f;
	case SCALE_500_PERCENT:
		return 5.0f;
	case SCALE_100_PERCENT:
	case DEVICE_SCALE_FACTOR_INVALID:
    default:
        return 1.0f;
    }
}

IMPLEMENT_DYNCREATE(CVisualManagerWin10Dark, CMFCVisualManagerOffice2007);

CVisualManagerWin10Dark::CVisualManagerWin10Dark()
{
    CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Style::Office2007_ObsidianBlack);

    m_clrWindows10ApplicationButton = RGB(0xFF, 0xFF, 0xFF);
    m_tabFaceBrush.CreateSolidBrush(m_clrWindows10ApplicationButton);
    m_tabBlackBrush.CreateSolidBrush(RGB(0x0,0x0,0x0));

    m_brGroupBackground.CreateSolidBrush(RGB(0x0, 0x0, 0x0));
    // load the UI elements
    m_uiElements.Load(IDB_UI_ELEMENTS);

    m_uiTB1.Load(IDB_TOGGLE_BOX_1);
    m_uiTB1.SetImageSize({ 40 , 40 });
}

void CVisualManagerWin10Dark::OnDrawCheckBox(CDC * pDC, CRect rect, BOOL bHighlighted, BOOL bChecked, BOOL bEnabled)
{
    CMFCToolBarImages CurImg;
    CurImg.SetImageSize({ rect.Height() , rect.Height() });
    CurImg.Load((rect.Height() > 16) ? IDB_CHECK_BOX_IMG_BIG : IDB_CHECK_BOX_IMG);

    CSize size(CurImg.GetImageSize());
    CRect imgRect(0, 0, size.cx, size.cy);

    if (bHighlighted)
    {
        CurImg.DrawEx(pDC, rect, 2, CMFCToolBarImages::ImageAlignHorzLeft, CMFCToolBarImages::ImageAlignVertCenter, imgRect);
        return;
    }

    if (!bChecked || !bEnabled)
        CurImg.DrawEx(pDC, rect, 0, CMFCToolBarImages::ImageAlignHorzLeft, CMFCToolBarImages::ImageAlignVertCenter, imgRect);
    else
        CurImg.DrawEx(pDC, rect, 2, CMFCToolBarImages::ImageAlignHorzLeft, CMFCToolBarImages::ImageAlignVertCenter, imgRect);
}

void CVisualManagerWin10Dark::OnDrawCheckBoxEx(CDC* pDC, CRect rect, int nState, BOOL bHighlighted, BOOL bPressed, BOOL bEnabled)
{
    CSize size(m_uiTB1.GetImageSize());
    unsigned int DPI = GetDpiForWindow(GetTopWindow(GetDesktopWindow()));

    CRect imgRect(0, 0, size.cx, size.cy);
    CRect ImgPos = rect;

    if (bHighlighted && !bPressed)
    {
        m_uiTB1.DrawEx(pDC, ImgPos, 2, CMFCToolBarImages::ImageAlignHorz::ImageAlignHorzStretch, CMFCToolBarImages::ImageAlignVert::ImageAlignVertStretch, imgRect);
        return;
    }

    if (!nState || !bEnabled)
        m_uiTB1.DrawEx(pDC, ImgPos, 1, CMFCToolBarImages::ImageAlignHorz::ImageAlignHorzStretch, CMFCToolBarImages::ImageAlignVert::ImageAlignVertStretch, imgRect);
    else
        m_uiTB1.DrawEx(pDC, ImgPos, 0, CMFCToolBarImages::ImageAlignHorz::ImageAlignHorzStretch, CMFCToolBarImages::ImageAlignVert::ImageAlignVertStretch, imgRect);
}

void CVisualManagerWin10Dark::OnDrawTab(
    CDC* pDC,
    CRect rectTab,
    int iTab,
    BOOL bIsActive,
    const CMFCBaseTabCtrl* pTabWnd)
{
    pDC->FillSolidRect(rectTab, m_clrWindows10Bar);

    CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
    pDC->SelectObject(pen);

    if (pTabWnd->GetLocation() == CMFCBaseTabCtrl::LOCATION_BOTTOM)
    {
        pDC->MoveTo(CPoint(rectTab.left, rectTab.bottom));
        pDC->LineTo(CPoint(rectTab.right - 1, rectTab.bottom));
    }
    else {
        pDC->MoveTo(CPoint(rectTab.left, rectTab.top));
        pDC->LineTo(CPoint(rectTab.right - 1, rectTab.top));
    }

    // the right hand side of the tab
    pDC->MoveTo(CPoint(rectTab.right - 1, rectTab.top));
    pDC->LineTo(CPoint(rectTab.right - 1, rectTab.bottom));
    pDC->MoveTo(CPoint(rectTab.left, rectTab.top));
    pDC->LineTo(CPoint(rectTab.left, rectTab.bottom));

    CString str;
    pTabWnd->GetTabLabel(iTab, str);

    if (!str.IsEmpty())
    {
        rectTab.DeflateRect(1, 1);

        if ((rectTab.Width() % 2) == 0)
        {
            rectTab.right--;
        }

        rectTab.OffsetRect(0, -1);

        COLORREF clrTextOld = pDC->SetTextColor(RGB(0xFF, 0xFF, 0xFF));
        pDC->DrawText(str, rectTab, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX);
        pDC->SetTextColor(clrTextOld);
    }

    CRect CloseRect;
    CloseRect.top = 5;
    CloseRect.bottom = rectTab.bottom - 3;
    CloseRect.left = rectTab.right - 20;
    CloseRect.right = rectTab.right - 3;

    OnDrawTabCloseButton(pDC, CloseRect, pTabWnd, true, false, false);

    if (bIsActive)
    {
        CPen pen(PS_SOLID, 2, RGB(0x2e, 0x1e, 0x8a));
        pDC->SelectObject(pen);

        pDC->MoveTo(CPoint(rectTab.left + 1, rectTab.top));
        pDC->LineTo(CPoint(rectTab.right - 1, rectTab.top));
    }
}

void CVisualManagerWin10Dark::OnDrawTabCloseButton(CDC* pDC, CRect rect, const CMFCBaseTabCtrl* pTabWnd, BOOL bIsHighlighted, BOOL bIsPressed, BOOL bIsDisabled)
{
    COLORREF clrTextOld = pDC->SetTextColor(RGB(0xFF, 0xFF, 0xFF));
    pDC->DrawText("x", rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX);
    pDC->SetTextColor(clrTextOld);
}

