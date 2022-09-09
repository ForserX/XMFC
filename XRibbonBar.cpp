#include "pch.h"
#include "XRibbonBar.h"
#include <afxribboninfoloader.h>
#include "XRibbonConstructor.h"
#include "XRibbonContextCaption.h"
#include "XRibbonCaptionButton.h"
#include "XRibbonButtonsGroup.h"
#include "XRibbonQuickAccessToolBar.h"

IMPLEMENT_DYNAMIC(XRibbonBar, CMFCRibbonBar)

BEGIN_MESSAGE_MAP(XRibbonBar, CMFCRibbonBar)
	ON_WM_PAINT()
END_MESSAGE_MAP()

XRibbonBar::XRibbonBar(BOOL bReplaceFrameCaption /*= TRUE*/)
	: CMFCRibbonBar(bReplaceFrameCaption)
{

}

XRibbonBar::~XRibbonBar()
{
	GroupTabs.clear();
}

XRibbonCategory* XRibbonBar::AddCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID,
	CSize sizeSmallImage, CSize sizeLargeImage, int nInsertAt, CRuntimeClass* pRTI)
{
	ASSERT_VALID(this);
	ENSURE(lpszName != NULL);

	XRibbonCategory* pCategory = NULL;

	if (pRTI != NULL)
	{
		pCategory = DYNAMIC_DOWNCAST(XRibbonCategory, pRTI->CreateObject());

		if (pCategory == NULL)
		{
			ASSERT(FALSE);
			return NULL;
		}

		pCategory->CommonInit(this, lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage);
	}
	else
	{
		pCategory = new XRibbonCategory(this, lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage);
	}

	if (nInsertAt < 0)
	{
		m_arCategories.Add(pCategory);
	}
	else
	{
		m_arCategories.InsertAt(nInsertAt, pCategory);
	}

	if (m_pActiveCategory == NULL)
	{
		pCategory->SetActive(true);
		m_pActiveCategory = pCategory;
	}

	m_bRecalcCategoryHeight = TRUE;
	m_bRecalcCategoryWidth = TRUE;

	if (!m_bSingleLevelAccessibilityMode)
	{
		m_Tabs.UpdateTabs(m_arCategories);
	}

	return pCategory;
}

XRibbonCategory* XRibbonBar::AddContextCategory(LPCTSTR lpszName, LPCTSTR lpszContextName, UINT uiContextID, AFX_RibbonCategoryColor clrContext, UINT uiSmallImagesResID, UINT uiLargeImagesResID, CSize sizeSmallImage, CSize sizeLargeImage, CRuntimeClass* pRTI)
{
	ASSERT_VALID(this);
	ENSURE(lpszContextName != NULL);
	ENSURE(uiContextID != 0);

	XRibbonCategory* pCategory = AddCategory(lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage, -1, pRTI);

	if (pCategory == NULL)
	{
		return NULL;
	}

	ASSERT_VALID(pCategory);

	pCategory->m_bIsVisible = FALSE;

	XRibbonContextCaption* pCaption = NULL;

	for (int i = 0; i < (int)m_arContextCaptions.GetSize(); i++)
	{
		ASSERT_VALID(m_arContextCaptions[i]);
		XRibbonContextCaption* pECaption = static_cast<XRibbonContextCaption*>(m_arContextCaptions[i]);

		if (pECaption->m_uiID == uiContextID)
		{
			pCaption = pECaption;
			pCaption->m_strText = lpszContextName;
			pCaption->m_Color = clrContext;
			break;
		}
	}

	if (pCaption == NULL)
	{
		pCaption = new XRibbonContextCaption(lpszContextName, uiContextID, clrContext);
		pCaption->m_pRibbonBar = this;

		m_arContextCaptions.Add(pCaption);
	}

	pCategory->SetTabColor(clrContext);
	pCategory->m_uiContextID = uiContextID;

	return pCategory;
}

void XRibbonBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	int i = 0;

	CMemDC memDC(dc, this);
	CDC* pDC = &memDC.GetDC();

	CRect rectClip;
	dc.GetClipBox(rectClip);

	CRgn rgnClip;

	if (!rectClip.IsRectEmpty())
	{
		rgnClip.CreateRectRgnIndirect(rectClip);
		pDC->SelectClipRgn(&rgnClip);
	}

	pDC->SetBkMode(TRANSPARENT);

	CRect rectClient;
	GetClientRect(rectClient);

	OnFillBackground(pDC, rectClient);

	CFont* pOldFont = pDC->SelectObject(GetFont());
	ENSURE(pOldFont != NULL);

	// Draw caption bar:
	if (!m_rectCaption.IsRectEmpty())
	{
		CRect rectFill = m_rectCaption;
		rectFill.top = 0;

		if (m_bIsTransparentCaption)
		{
			pDC->FillSolidRect(rectFill, RGB(0, 0, 0));

			CMFCToolBarImages::m_bIsDrawOnGlass = TRUE;
		}

		CMFCVisualManager::GetInstance()->OnDrawRibbonCaption(pDC, this, m_rectCaption, m_rectCaptionText);

		for (i = 0; i < AFX_RIBBON_CAPTION_BUTTONS; i++)
		{
			if (!m_CaptionButtons[i].GetRect().IsRectEmpty())
			{
				((XRibbonCaptionButton*)&m_CaptionButtons[i])->OnDraw(pDC);
			}
		}

		for (i = 0; i < (int)m_arContextCaptions.GetSize(); i++)
		{
			ASSERT_VALID(m_arContextCaptions[i]);
			XRibbonContextCaption* pECaption = static_cast<XRibbonContextCaption*>(m_arContextCaptions[i]);
			pECaption->OnDraw(pDC);
		}

		CMFCToolBarImages::m_bIsDrawOnGlass = FALSE;
	}

	if (m_bIsTransparentCaption && m_bQuickAccessToolbarOnTop)
	{
		CMFCToolBarImages::m_bIsDrawOnGlass = TRUE;
	}

	// Draw quick access toolbar:
	COLORREF cltTextOld = (COLORREF)-1;
	COLORREF cltQATText = CMFCVisualManager::GetInstance()->GetRibbonQuickAccessToolBarTextColor();

	if (cltQATText != (COLORREF)-1)
	{
		cltTextOld = pDC->SetTextColor(cltQATText);
	}

	// Apper toolbar (print, new file, save)
	((XRibbonQuickAccessToolBar*)&m_QAToolbar)->OnDraw(pDC);

	if (cltTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor(cltTextOld);
	}

	CMFCToolBarImages::m_bIsDrawOnGlass = FALSE;

	// Draw active category:
	if (m_pActiveCategory != NULL && m_dwHideFlags == 0)
	{
		ASSERT_VALID(m_pActiveCategory);
		m_pActiveCategory->OnDraw(pDC);
	}

	// Draw tabs:
	CRect rectTabs = rectClient;
	rectTabs.top = m_rectCaption.IsRectEmpty() ? rectClient.top : m_rectCaption.bottom;
	rectTabs.bottom = rectTabs.top + m_nTabsHeight;

	COLORREF clrTextTabs = CMFCVisualManager::GetInstance()->OnDrawRibbonTabsFrame(pDC, this, rectTabs);
	CString CurGroup = "";
	int LastGroupTab = 0;

	CPen leafPen(PS_SOLID, 1, GetGlobalData()->clrWindowFrame);

	for (i = 0; i < (int)m_arCategories.GetSize(); i++)
	{
		XRibbonCategory* pCategory = static_cast<XRibbonCategory*>(m_arCategories[i]);
		ASSERT_VALID(pCategory);

		if (pCategory->IsVisible())
		{
			if (pCategory->IsGroup() && CurGroup != pCategory->GetGroupName())
			{
				CurGroup = pCategory->GetGroupName();

				LastGroupTab = i + GroupTabs[CurGroup.operator LPCSTR()] - 1;
				XRibbonCategory* pLastCat = static_cast<XRibbonCategory*>(m_arCategories[LastGroupTab]);
				CRect LastTabRect = pLastCat->m_Tab.GetRect();
				CRect TabRect = pCategory->m_Tab.GetRect();

				TabRect.right = LastTabRect.right;
				TabRect.bottom = TabRect.top + 2;
				TabRect.top = 15;

				CBrush FrameBr(GetGlobalData()->clrWindowFrame);
				pDC->FillRect(TabRect, &GetGlobalData()->brBtnFace);
				pDC->FrameRect(TabRect, &FrameBr);

				TabRect.top = TabRect.bottom / 2;
				TabRect.top -= 1;

				TabRect.left += (TabRect.right - TabRect.left - (7 * CurGroup.GetLength())) / 2;

				pDC->SetTextColor(GetGlobalData()->clrWindowText);
				pDC->DrawText(CurGroup, TabRect, 0);

				pCategory->m_Tab.OnDraw(pDC);

				pDC->SelectObject(leafPen);
				TabRect = pCategory->m_Tab.GetRect();
				pDC->MoveTo(TabRect.left, TabRect.top);
				pDC->LineTo(TabRect.left, TabRect.bottom);

				continue;
			}

			pCategory->m_Tab.OnDraw(pDC);

			if (LastGroupTab == i)
			{
				CRect TabRect = pCategory->m_Tab.GetRect();

				pDC->SelectObject(leafPen);
				pDC->MoveTo(TabRect.right - 1, TabRect.top);
				pDC->LineTo(TabRect.right - 1, TabRect.bottom);
			}
		}
	}

	// Draw elements on right of tabs:
	COLORREF clrTextOld = (COLORREF)-1;
	if (clrTextTabs != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor(clrTextTabs);
	}

	((XRibbonButtonsGroup*)&m_TabElements)->OnDraw(pDC);

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor(clrTextOld);
	}

	// Draw main button:
	if (m_pMainButton != NULL)
	{
		ASSERT_VALID(m_pMainButton);

		if (!m_pMainButton->GetRect().IsRectEmpty())
		{
			CMFCVisualManager::GetInstance()->OnDrawRibbonApplicationButton(pDC, m_pMainButton);

			m_pMainButton->OnDraw(pDC);
		}
	}

	pDC->SelectObject(pOldFont);
	pDC->SelectClipRgn(NULL);
}

BOOL XRibbonBar::LoadFromResource(LPCTSTR lpszXMLResID, LPCTSTR lpszResType /*= RT_RIBBON*/, HINSTANCE hInstance /*= NULL*/)
{
	ASSERT_VALID(this);

	CMFCRibbonInfo info;
	CMFCRibbonInfoLoader loader(info);

	if (!loader.Load(lpszXMLResID, lpszResType, hInstance))
	{
		TRACE0("Cannot load ribbon from resource\n");
		return FALSE;
	}
	XRibbonConstructor constr(info);
	constr.ConstructRibbonBar(*this);

	for (size_t Iter = 0; Iter < m_arCategories.GetSize(); Iter++)
	{
		XRibbonCategory* pCategory = static_cast<XRibbonCategory*>(m_arCategories[Iter]);

		if (pCategory->IsGroup())
		{
			std::string TryName = pCategory->GetGroupName().operator LPCSTR();
			auto FindIter = GroupTabs.find(TryName);

			if (FindIter != GroupTabs.end())
			{
				GroupTabs[TryName] += 1;
			}
			else
			{
				GroupTabs[TryName] = 1;
			}
		}
	}


	return TRUE;
}

BOOL XRibbonBar::LoadFromResource(UINT uiXMLResID, LPCTSTR lpszResType /*= RT_RIBBON*/, HINSTANCE hInstance /*= NULL*/)
{
	return CMFCRibbonBar::LoadFromResource(uiXMLResID, lpszResType, hInstance);
}
