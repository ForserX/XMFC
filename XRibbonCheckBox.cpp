#include "pch.h"
#include "XRibbonCheckBox.h"

IMPLEMENT_DYNCREATE(XRibbonCheckBox, CMFCRibbonCheckBox)

const int nTextMarginLeft = 4;
const int nTextMarginRight = 6;

XRibbonCheckBox::XRibbonCheckBox()
{
}

XRibbonCheckBox::XRibbonCheckBox(UINT nID, LPCTSTR lpszText)
	: CMFCRibbonCheckBox(nID, lpszText)
{

}

XRibbonCheckBox::~XRibbonCheckBox()
{
}

void XRibbonCheckBox::OnDraw(CDC* pDC)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	if (m_rect.IsRectEmpty())
	{
		return;
	}

	float DPIScaleFactorX = float(MainWnd->DPI.x) / 96.0f;
	float DPIScaleFactorY = float(MainWnd->DPI.y) / 96.0f;

	float EffectiveScalingX = std::max(DPIScaleFactorX, MainWnd->ScaleFactor);
	float EffectiveScalingY = std::max(DPIScaleFactorY, MainWnd->ScaleFactor);

	CSize sizeCheckBox = CSize(20, 20);

	sizeCheckBox.cx *= (long)EffectiveScalingX;
	sizeCheckBox.cy *= (long)EffectiveScalingY;

	// Draw check box:
	CRect rectCheck = m_rect;
	rectCheck.DeflateRect(m_szMargin);
	rectCheck.left++;
	rectCheck.right = rectCheck.left + sizeCheckBox.cx;
	rectCheck.top = rectCheck.CenterPoint().y - sizeCheckBox.cx / 2;

	rectCheck.bottom = rectCheck.top + sizeCheckBox.cy;

	const BOOL bIsHighlighted = (IsHighlighted() || IsFocused()) && !IsDisabled();
	int nState = 0;

	if (m_bIsChecked == 2)
	{
		nState = 2;
	}
	else if (IsChecked() || (IsPressed() && bIsHighlighted))
	{
		nState = 1;
	}

	CMFCVisualManager::GetInstance()->OnDrawCheckBoxEx(pDC, rectCheck, nState,
		bIsHighlighted, IsPressed() && bIsHighlighted, !IsDisabled());

	// Draw text:
	COLORREF clrTextOld = (COLORREF)-1;

	if (m_bIsDisabled)
	{
		if (m_bQuickAccessMode)
		{
			clrTextOld = pDC->SetTextColor(CMFCVisualManager::GetInstance()->GetRibbonQuickAccessToolBarTextColor(TRUE));
		}
		else
		{
			clrTextOld = pDC->SetTextColor(CMFCVisualManager::GetInstance()->GetToolbarDisabledTextColor());
		}
	}

	CRect rectText = m_rect;
	rectText.left = rectCheck.right + nTextMarginLeft;

	DrawRibbonText(pDC, m_strText, rectText, DT_SINGLELINE | DT_VCENTER);

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor(clrTextOld);
	}

	if (IsFocused())
	{
		CRect rectFocus = rectText;
		rectFocus.OffsetRect(-nTextMarginLeft / 2, 0);
		rectFocus.DeflateRect(0, 2);

		pDC->DrawFocusRect(rectFocus);
	}
}

CSize XRibbonCheckBox::GetIntermediateSize(CDC* pDC)
{
	m_szMargin = CSize(2, 3);

	float DPIScaleFactorX = float(MainWnd->DPI.x) / 96.0f;
	float EffectiveScalingX = std::max(DPIScaleFactorX, MainWnd->ScaleFactor);

	CSize sizeCheckBox = CSize(20, 20);

	sizeCheckBox.cx *= (long)EffectiveScalingX;

	int cx = sizeCheckBox.cx + m_sizeTextRight.cx + nTextMarginLeft + nTextMarginRight + m_szMargin.cx;
	int cy = std::max(sizeCheckBox.cy, m_sizeTextRight.cy) + 2 * m_szMargin.cy;

	return CSize(cx, cy);
}

