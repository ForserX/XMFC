#include "pch.h"
#include "XRibbonRadioBox.h"

void XRibbonRadioBox::OnDraw(CDC* pDC)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	if (m_rect.IsRectEmpty())
	{
		return;
	}

	const CSize sizeCheckBox = CSize(MY_RADIO_BUTTON_DEFAULT_SIZE, MY_RADIO_BUTTON_DEFAULT_SIZE);

	// Draw check box:
	CRect rectCheck = m_rect;
	rectCheck.DeflateRect(m_szMargin);
	rectCheck.left++;
	rectCheck.right = rectCheck.left + sizeCheckBox.cx;
	rectCheck.top = rectCheck.CenterPoint().y - sizeCheckBox.cx / 2;

	rectCheck.bottom = rectCheck.top + sizeCheckBox.cy;

	const BOOL bIsHighlighted = (IsHighlighted() || IsFocused()) && !IsDisabled();

	pDC->DrawFrameControl(rectCheck, DFC_BUTTON, DFCS_BUTTONRADIO | (IsChecked() || (IsPressed() && bIsHighlighted) ? DFCS_CHECKED : 0));

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
}