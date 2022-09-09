#include "pch.h"
#include "XRibbonCategory.h"
#include "XRibbonPanel.h"

static const int nPanelMarginLeft = 2;
static const int nPanelMarginRight = 2;
static const int nPanelMarginTop = 3;
static const int nPanelMarginBottom = 4;

CMFCRibbonPanel* XRibbonCategory::AddPanel(LPCTSTR lpszPanelName, HICON hIcon, CRuntimeClass* pRTI)
{
	ASSERT_VALID(this);
	ENSURE(lpszPanelName != NULL);

	XRibbonPanel* pPanel = nullptr;

	if (pRTI != NULL)
	{
		pPanel = DYNAMIC_DOWNCAST(XRibbonPanel, pRTI->CreateObject());

		if (pPanel == NULL)
		{
			ASSERT(FALSE);
			return NULL;
		}

		pPanel->CommonInit(lpszPanelName, hIcon);
	}
	else
	{
		pPanel = new XRibbonPanel(lpszPanelName, hIcon);
	}

	m_arPanels.Add(pPanel);

	pPanel->SetAllParent(this);

	m_nLastCategoryWidth = -1;
	m_nMinWidth = -1;
	return pPanel;
}

bool XRibbonCategory::IsGroup() const
{
	return bHaveGroup;
}

void XRibbonCategory::SetGroup(const std::string_view Name)
{
	GroupName = Name;
	bHaveGroup = true;
}

CString XRibbonCategory::GetGroupName() const
{
	return CString(GroupName.c_str());
}

void XRibbonCategory::OnDraw(CDC* pDC)
{
	if (m_rect.IsRectEmpty())
	{
		return;
	}

	CMFCVisualManager::GetInstance()->OnDrawRibbonCategory(pDC, this, m_rect);

	BOOL bClip = FALSE;

	CRgn rgnClip;

	if (!m_ScrollLeft.GetRect().IsRectEmpty() ||
		!m_ScrollRight.GetRect().IsRectEmpty())
	{
		CRect rectClient = m_rect;
		rectClient.DeflateRect(nPanelMarginLeft, nPanelMarginTop,
			nPanelMarginRight, nPanelMarginBottom);

		rgnClip.CreateRectRgnIndirect(rectClient);
		pDC->SelectClipRgn(&rgnClip);

		bClip = TRUE;
	}

	for (int i = 0; i < m_arPanels.GetSize(); i++)
	{
		XRibbonPanel* pPanel = static_cast<XRibbonPanel*>(m_arPanels[i]);
		ASSERT_VALID(pPanel);

		pPanel->DoPaint(pDC);
	}

	if (bClip)
	{
		pDC->SelectClipRgn(NULL);
	}
}

void XRibbonCategory::CommonInit(CMFCRibbonBar* pParentRibbonBar, LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID, CSize sizeSmallImage, CSize sizeLargeImage)
{
	CMFCRibbonCategory::CommonInit(pParentRibbonBar, lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage);
}
