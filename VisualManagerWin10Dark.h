#pragma once
#include "framework.h"
#include <dwmapi.h>
#include <afxvisualmanagerwindows.h>

#pragma comment(lib, "Dwmapi.lib")

class CVisualManagerWin10Dark : public CMFCVisualManagerOffice2007
{
	DECLARE_DYNCREATE(CVisualManagerWin10Dark);

	CMFCToolBarImages m_uiElements;
	CMFCToolBarImages m_uiTB1;

private:
	CVisualManagerWin10Dark();

public:
	virtual ~CVisualManagerWin10Dark() = default;

	// This is the color of a docking pane's caption
	virtual COLORREF OnDrawPaneCaption(CDC* pDC, CDockablePane* pBar, BOOL bActive, CRect rectCaption, CRect rectButtons)
	{
		CBrush brush(RGB(61, 61, 61));
		pDC->FillRect(rectCaption, &brush);
		pDC->FillRect(rectButtons, &brush);

		return RGB(255, 255, 255);
	}

	virtual COLORREF GetAutoHideButtonTextColor(CMFCAutoHideButton* pButton)
	{
		if (pButton->IsHighlighted())
		{
			return 0xd9d507; // желтый
		}
		else
		{
			return RGB(113, 96, 232); // светлый фиолетовый
		}
	}

	virtual void OnFillAutoHideButtonBackground(CDC* pDC, CRect rect, CMFCAutoHideButton* pButton)
	{
		if (pButton->IsHighlighted())
		{
			pDC->FillSolidRect(rect, RGB(75, 75, 75)); // серый
		}
	}

	virtual COLORREF OnDrawPropertySheetListItem(CDC* pDC, CMFCPropertySheet* pParent, CRect rect, BOOL bIsHighlihted, BOOL bIsSelected)
	{
		static_cast<void>(bIsHighlihted);
		static_cast<void>(bIsSelected);
		static_cast<void>(pParent);
		pDC->FillSolidRect(rect, RGB(255, 0, 0));
		return RGB(0, 255, 0);
	}

	// This is the are behind the ribbon where there are no categories
	virtual void OnDrawRibbonCategory(CDC* pDC, CMFCRibbonCategory* pCategory, CRect rectCategory)
	{
		static_cast<void>(pCategory);
		pDC->FillSolidRect(rectCategory, m_clrWindows10Bar);

		CPen pen(PS_SOLID, 1, RGB(113, 96, 232)); // светлый фиолетовый
		pDC->SelectObject(pen);
		pDC->MoveTo(CPoint(rectCategory.left, rectCategory.top));
		pDC->LineTo(CPoint(rectCategory.right - 1, rectCategory.top));
	}

	virtual COLORREF OnFillRibbonMainPanelButton(CDC* pDC, CMFCRibbonButton* pButton)
	{
		CString text = pButton->GetText();
		if (!text.IsEmpty()) {
			pDC->FillSolidRect(pButton->GetRect(), m_clrWindows10Bar);
			return RGB(77, 0, 255);
		}
		return RGB(77, 0, 255);
	}

	virtual void OnDrawRibbonMainPanelButtonBorder(CDC* pDC, CMFCRibbonButton* pButton)
	{
		CString text = pButton->GetText();
		if (!text.IsEmpty()) {
			pDC->SelectStockObject(BLACK_PEN);
			pDC->SelectStockObject(NULL_BRUSH);
			pDC->Rectangle(pButton->GetRect());
		}
	}

	virtual void OnDrawRibbonMainPanelFrame(CDC* pDC, CMFCRibbonMainPanel* pPanel, CRect rect)
	{
		static_cast<void>(pPanel);
		pDC->FillSolidRect(rect, m_clrWindows10Bar);
	}

	virtual void OnFillRibbonMenuFrame(CDC* pDC, CMFCRibbonMainPanel* pPanel, CRect rect)
	{
		static_cast<void>(rect);
		pDC->FillSolidRect(pPanel->GetRect(), RGB(254, 254, 255));
	}

	virtual void OnDrawRibbonRecentFilesFrame(CDC* pDC, CMFCRibbonMainPanel* pPanel, CRect rect)
	{
		static_cast<void>(pPanel);
		pDC->FillSolidRect(rect, RGB(255, 0, 0));
	}

	virtual COLORREF OnFillRibbonButton(CDC* pDC, CMFCRibbonButton* pButton)
	{
		if (pButton->GetParentPanel() && pButton->GetParentPanel()->IsKindOf(RUNTIME_CLASS(CMFCRibbonMainPanel)))
		{
			// RHS of recent files does not have large icons
			if (pButton->IsLargeImage())
			{
				if (pButton->IsHighlighted())
				{
					// #EDF4FC
					pDC->FillSolidRect(pButton->GetRect(), RGB(57, 62, 68));

					// #A8D2FD
					CPen pen(PS_SOLID, 1, RGB(35, 40, 46));
					pDC->SelectObject(pen);
					pDC->SelectStockObject(NULL_BRUSH);
					pDC->Rectangle(pButton->GetRect());
				}
				else
				{
					pDC->FillSolidRect(pButton->GetRect(), RGB(35, 40, 46));
				}
				return RGB(255, 255, 255);
			}
		}
		return RGB(255, 255, 255);
	}

	virtual COLORREF GetToolbarButtonTextColor(CMFCToolBarButton* pButton, CMFCVisualManager::AFX_BUTTON_STATE state)
	{
		return RGB(255, 255, 255);
	}

	virtual COLORREF OnDrawMenuLabel(CDC* pDC, CRect rect)
	{
		pDC->FillSolidRect(rect, m_clrWindows10Bar);
		return RGB(255, 255, 255);
	}

	virtual COLORREF GetMenuItemTextColor(CMFCToolBarMenuButton* pButton, BOOL bHighlighted, BOOL bDisabled) override
	{
		if (bDisabled)
		{
			return RGB(75, 75, 75); // серый
		}
		else
		{
			return GetGlobalData()->clrMenuText;
		}
	}

	virtual void OnHighlightMenuItem(CDC* pDC, CMFCToolBarMenuButton* pButton, CRect rect, COLORREF& clrText) override
	{
		static_cast<void>(pButton);

		// #EDF4FC
		pDC->FillSolidRect(rect, RGB(73, 102, 140)); // серо-синий

		// #A8D2FD
		CPen pen(PS_SOLID, 1, RGB(92, 103, 115)); // серый
		pDC->SelectObject(pen);
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->Rectangle(rect);
		clrText = RGB(255, 255, 255);
	}
	virtual void OnDrawCheckBox(CDC* pDC, CRect rect, BOOL bHighlighted, BOOL bChecked, BOOL bEnabled);

	virtual void OnDrawMenuCheck(CDC* pDC, CMFCToolBarMenuButton* pButton, CRect rect, BOOL bHighlight, BOOL bIsRadio)
	{
		static_cast<void>(pButton);
		static_cast<void>(bHighlight);
		static_cast<void>(bIsRadio);

		rect.InflateRect(0, 1);

		if (bHighlight)
		{
			pDC->SelectStockObject(NULL_PEN);
			pDC->FillSolidRect(rect, RGB(77, 64, 87));

			CPen pen(PS_SOLID, 1, RGB(54, 41, 77));
			pDC->SelectObject(pen);
			pDC->SelectStockObject(NULL_BRUSH);
			pDC->Rectangle(rect);
		}
		else {
			pDC->SelectStockObject(NULL_PEN);
			pDC->FillSolidRect(rect, RGB(206, 229, 252));

			CPen pen(PS_SOLID, 1, RGB(77, 64, 87));
			pDC->SelectObject(pen);
			pDC->SelectStockObject(NULL_BRUSH);
			pDC->Rectangle(rect);
		}

		CSize size(m_uiElements.GetImageSize());
		CRect imgRect(0, 0, size.cx, size.cy);

		if ((pButton->m_nStyle & TBBS_DISABLED) == TBBS_DISABLED)
		{
			imgRect.OffsetRect(0, size.cy);
		}

		m_uiElements.DrawEx(pDC, rect, 0, CMFCToolBarImages::ImageAlignHorzCenter, CMFCToolBarImages::ImageAlignVertCenter, imgRect);
	}

	virtual void OnDrawCheckBoxEx(CDC* pDC, CRect rect, int nState, BOOL bHighlighted, BOOL bPressed, BOOL bEnabled);

	// The ribbons tab at the top where the categories are
	virtual COLORREF OnDrawRibbonCategoryTab(CDC* pDC, CMFCRibbonTab* pTab, BOOL bIsActive)
	{
		// the background of the category tab
		if (bIsActive)
		{
			pDC->FillSolidRect(pTab->GetRect(), m_clrWindows10Bar);

			CPen pen(PS_SOLID, 1, 0x00498a); // оранжевый
			pDC->SelectObject(pen);
			pDC->MoveTo(CPoint(pTab->GetRect().left, pTab->GetRect().bottom));
			pDC->LineTo(CPoint(pTab->GetRect().left, pTab->GetRect().top));
			pDC->LineTo(CPoint(pTab->GetRect().right - 1, pTab->GetRect().top));
			pDC->LineTo(CPoint(pTab->GetRect().right - 1, pTab->GetRect().bottom));

			CPen pen2(PS_SOLID, 1, m_clrWindows10Bar);
			pDC->SelectObject(pen2);
			pDC->LineTo(CPoint(pTab->GetRect().left, pTab->GetRect().bottom));
		}
		else
		{
			CBrush brush(RGB(31, 31, 31));
			pDC->FillRect(pTab->GetRect(), &brush);

			CPen pen(PS_SOLID, 1, RGB(64, 19, 141)); // темно-фиолетовый
			pDC->SelectObject(pen);
			pDC->MoveTo(CPoint(pTab->GetRect().left, pTab->GetRect().bottom));
			pDC->LineTo(CPoint(pTab->GetRect().right - 1, pTab->GetRect().bottom));

			pDC->SelectStockObject(BLACK_PEN);
		}
		// the color of the text on the tab

		// the color of the non selected tab text
		return RGB(255, 255, 255);
	}

	virtual COLORREF OnDrawRibbonPanel(CDC* pDC, CMFCRibbonPanel* pPanel, CRect rectPanel, CRect rectCaption)
	{
		static_cast<void>(pPanel);
		// the color of the ribbon
		pDC->FillSolidRect(rectPanel, m_clrWindows10Bar);
		pDC->FillSolidRect(rectCaption, m_clrWindows10Bar);

		// This is the color of controls on the ribbon
		return RGB(255, 255, 255);
	}

	// this is the caption at the bottom on each panel
	virtual void OnDrawRibbonPanelCaption(CDC* pDC, CMFCRibbonPanel* pPanel, CRect rectCaption)
	{
		pDC->FillSolidRect(rectCaption, m_clrWindows10Bar);

		CString str = pPanel->GetName();

		if (!str.IsEmpty())
		{
			rectCaption.DeflateRect(1, 1);

			if ((rectCaption.Width() % 2) == 0)
			{
				rectCaption.right--;
			}

			rectCaption.OffsetRect(0, -1);

			COLORREF clrTextOld = pDC->SetTextColor(RGB(255, 255, 255));
			pDC->DrawText(str, rectCaption, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX);
			pDC->SetTextColor(clrTextOld);
		}

		// draw the separator on the right hand side
		CPen pen(PS_SOLID, 1, RGB(64, 64, 64)); // какой-то серый
		pDC->SelectObject(pen);
		CRect panelRect = pPanel->GetRect();
		pDC->MoveTo(panelRect.right - 1, panelRect.top + 2);
		pDC->LineTo(panelRect.right - 1, panelRect.bottom - 2);
	}

	// The color behind the category tabs
	virtual COLORREF OnDrawRibbonTabsFrame(CDC* pDC, CMFCRibbonBar* pWndRibbonBar, CRect rectTab)
	{
		static_cast<void>(pWndRibbonBar);
		CBrush brush(RGB(48, 48, 48));
		pDC->FillRect(rectTab, &brush);

		// color return is reserved by Microsoft
		return static_cast<COLORREF>(-1);
	}

	virtual COLORREF OnDrawRibbonStatusBarPane(CDC* pDC, CMFCRibbonStatusBar* pBar, CMFCRibbonStatusBarPane* pPane)
	{
		static_cast<void>(pBar);
		// this is the color of the names
		CBrush brush(RGB(46, 38, 119)); //brush 2e2677 фиолетово-синий
		pDC->FillRect(pPane->GetRect(), &brush);

		// this is the text color
		return RGB(255, 255, 255);  //text
	}

	virtual void OnFillBarBackground(CDC* pDC, CBasePane* pBar, CRect rectClient, CRect rectClip, BOOL bNCArea = FALSE)
	{
		static_cast<void>(bNCArea);
		static_cast<void>(rectClip);
		static_cast<void>(pBar);
		CBrush brush(GetGlobalData()->clrBarFace);
		pDC->FillRect(rectClient, &brush);
	}

	virtual BOOL OnEraseTabsFrame(CDC* pDC, CRect rect, const CMFCBaseTabCtrl* pTabWnd)
	{
		static_cast<void>(pTabWnd);
		CBrush brush(RGB(31, 31, 31));
		pDC->FillRect(rect, &brush);
		return TRUE;
	}

	virtual void OnDrawStatusBarSizeBox(CDC* pDC, CMFCStatusBar* pStatBar, CRect rectSizeBox)
	{
		static_cast<void>(pStatBar);
		CBrush brush(RGB(31, 31, 31));
		pDC->FillRect(rectSizeBox, &brush);
	}

	virtual void OnDrawTab(CDC* pDC, CRect rectTab, int iTab, BOOL bIsActive, const CMFCBaseTabCtrl* pTabWnd);

	virtual void OnFillTab(CDC* pDC, CRect rectFill, CBrush* pbrFill, int iTab, BOOL bIsActive, const CMFCBaseTabCtrl* pTabWnd)
	{
		static_cast<void>(pTabWnd);
		static_cast<void>(bIsActive);
		static_cast<void>(iTab);
		static_cast<void>(pbrFill);

		pDC->FillRect(rectFill, &m_tabBlackBrush);
	}
	virtual void OnDrawTabCloseButton(CDC* pDC, CRect rect, const CMFCBaseTabCtrl* pTabWnd, BOOL bIsHighlighted, BOOL bIsPressed, BOOL bIsDisabled);

	virtual COLORREF OnFillCommandsListBackground(CDC* pDC, CRect rect, BOOL bIsSelected = FALSE)
	{
		rect.left = 0;

		pDC->FillRect(rect, &m_tabBlackBrush);
		if (bIsSelected)
		{
			pDC->Draw3dRect(rect, RGB(255, 255, 255), RGB(255, 255, 255));
			return RGB(255, 255, 255);
		}

		return GetGlobalData()->clrBarText;
	}

	virtual void GetTabFrameColors(
		const CMFCBaseTabCtrl* pTabWnd,
		COLORREF& clrDark,
		COLORREF& clrBlack,
		COLORREF& clrHighlight,
		COLORREF& clrFace,
		COLORREF& clrDarkShadow,
		COLORREF& clrLight,
		CBrush*& pbrFace,
		CBrush*& pbrBlack
	) {
		static_cast<void>(pTabWnd);
		clrDark = 0;
		clrBlack = 0;
		clrHighlight = 0;
		clrFace = 0;
		clrDarkShadow = 0;
		clrLight = 0;

		pbrFace = &m_tabFaceBrush;
		pbrBlack = &m_tabBlackBrush;
	}

	virtual COLORREF GetTabTextColor(
		const CMFCBaseTabCtrl* pTabWnd,
		int iTab,
		BOOL bIsActive
	) {
		static_cast<void>(iTab);
		static_cast<void>(pTabWnd);
		static_cast<void>(bIsActive);
		return RGB(255, 255, 255);
	}

	virtual COLORREF GetPropertyGridGroupTextColor(CMFCPropertyGridCtrl* pPropList)
	{
		static_cast<void>(pPropList); return RGB(255, 255, 255);
	}

	virtual COLORREF GetPropertyGridGroupColor(CMFCPropertyGridCtrl* pPropList)
	{
		static_cast<void>(pPropList);
		return RGB(21, 21, 21);
	}

	virtual void OnDrawComboDropButton(CDC* pDC, CRect rect, BOOL bDisabled, BOOL bIsDropped, BOOL bIsHighlighted, CMFCToolBarComboBoxButton* pButton)
	{
		pDC->FillSolidRect(rect, RGB(113, 96, 232)); // светлый фиолетовый
		CMenuImages::Draw(pDC, CMenuImages::IdArrowDown, rect);
	}

	virtual COLORREF GetHighlightMenuItemColor() const
	{
		return RGB(255, 255, 255);
	}

	virtual void OnDrawTask(CDC* pDC, CMFCTasksPaneTask* pTask, CImageList* pIcons, BOOL bIsHighlighted = FALSE, BOOL bIsSelected = FALSE)
	{
		CRect rectGroup = pTask->m_rect;

		CRect rectFill = rectGroup;
		rectFill.DeflateRect(1, 1);

		pDC->FillSolidRect(rectFill, RGB(31, 31, 31));
	}

	virtual void OnDrawCaptionBarInfoArea(
		CDC* pDC,
		CMFCCaptionBar* pBar,
		CRect rect)
	{
		static_cast<void>(pBar);
		pDC->FillSolidRect(rect, GetGlobalData()->clrWindow); //brush 2e2677);

		CPen pen(PS_SOLID, 1, GetGlobalData()->clrWindowFrame);
		pDC->SelectObject(pen);

		pDC->MoveTo(CPoint(rect.left, rect.top));
		pDC->LineTo(CPoint(rect.right, rect.top));
		pDC->LineTo(CPoint(rect.right, rect.bottom));
		pDC->LineTo(CPoint(rect.left, rect.bottom));
	}

	virtual COLORREF GetCaptionBarTextColor(CMFCCaptionBar* pBar)
	{
		return RGB(255, 255, 255);
	}

	virtual void OnDrawTabsButtonBorder(CDC* pDC, CRect& rect, CMFCButton* pButton, UINT uiState, CMFCBaseTabCtrl* pWndTab) override
	{
		static_cast<void>(pButton);
		static_cast<void>(rect);
		static_cast<void>(uiState);
		CBrush brush(GetGlobalData()->clrHilite);
		CRect tabRect;
		pWndTab->GetTabsRect(tabRect);
		pDC->FillRect(tabRect, &brush);
	}

	virtual void OnEraseTabsArea(CDC* pDC, CRect rect, const CMFCBaseTabCtrl* pTabWnd) {
		static_cast<void>(pTabWnd);
		pDC->FillSolidRect(rect, RGB(31, 31, 31));
	}

	void OnUpdateSystemColors() override
	{
		BOOL USE_DARK_MODE = true;
		BOOL SET_IMMERSIVE_DARK_MODE_SUCCESS = SUCCEEDED(DwmSetWindowAttribute(
			AfxGetMainWnd()->m_hWnd, DWMWINDOWATTRIBUTE::DWMWA_USE_IMMERSIVE_DARK_MODE,
			&USE_DARK_MODE, sizeof(USE_DARK_MODE)));

		GetGlobalData()->clrBarFace = RGB(31, 31, 31);
		GetGlobalData()->clrBtnFace = RGB(31, 31, 31);

		GetGlobalData()->clrBarShadow = RGB(64, 19, 141);
		GetGlobalData()->clrBtnShadow = RGB(64, 19, 141);

		GetGlobalData()->clrBarDkShadow = RGB(64, 19, 141);
		GetGlobalData()->clrBtnDkShadow = RGB(64, 19, 141);

		GetGlobalData()->clrBarLight = RGB(181, 181, 181);
		GetGlobalData()->clrBtnLight = RGB(48, 48, 48);

		GetGlobalData()->clrBarHilite = ::GetSysColor(COLOR_BTNHIGHLIGHT);
		GetGlobalData()->clrBtnHilite = RGB(56, 0, 102); // темно-фиолетовый

		GetGlobalData()->clrBarText = RGB(255, 255, 255); // --
		GetGlobalData()->clrBtnText = RGB(255, 255, 255); // --
		GetGlobalData()->clrGrayedText = RGB(181, 181, 181); // --
		GetGlobalData()->clrWindowFrame = RGB(64, 19, 141); // фиолетовый

		GetGlobalData()->clrHilite = RGB(48, 48, 48);
		GetGlobalData()->clrTextHilite = RGB(255, 255, 0); // желтый

		GetGlobalData()->clrBarWindow = RGB(48, 48, 48);
		GetGlobalData()->clrWindow = RGB(31, 31, 31);

		GetGlobalData()->clrWindowText = RGB(255, 255, 255);
		GetGlobalData()->clrCaptionText = RGB(255, 255, 255);
		GetGlobalData()->clrMenuText = RGB(255, 255, 255);
		GetGlobalData()->clrActiveCaption = RGB(31, 31, 31);
		GetGlobalData()->clrInactiveCaption = RGB(31, 31, 31);
		GetGlobalData()->clrActiveCaptionGradient = RGB(31, 31, 31);
		GetGlobalData()->clrInactiveCaptionGradient = RGB(31, 31, 31); // какой-то серый
		GetGlobalData()->clrInactiveCaptionText = RGB(255, 255, 255); // белый

		GetGlobalData()->clrActiveBorder = RGB(0, 0, 255);
		GetGlobalData()->clrInactiveBorder = RGB(0, 0, 255);

		GetGlobalData()->brBtnFace.DeleteObject();
		GetGlobalData()->brBtnFace.CreateSolidBrush(GetGlobalData()->clrBtnFace);

		GetGlobalData()->brBarFace.DeleteObject();
		GetGlobalData()->brBarFace.CreateSolidBrush(GetGlobalData()->clrBarFace);

		GetGlobalData()->brActiveCaption.DeleteObject();
		GetGlobalData()->brActiveCaption.CreateSolidBrush(GetGlobalData()->clrActiveCaption);

		GetGlobalData()->brInactiveCaption.DeleteObject();
		GetGlobalData()->brInactiveCaption.CreateSolidBrush(GetGlobalData()->clrInactiveCaption);

		GetGlobalData()->brHilite.DeleteObject();
		GetGlobalData()->brHilite.CreateSolidBrush(GetGlobalData()->clrHilite);

		GetGlobalData()->brBlack.DeleteObject();
		GetGlobalData()->brBlack.CreateSolidBrush(GetGlobalData()->clrBtnDkShadow);

		GetGlobalData()->brWindow.DeleteObject();
		GetGlobalData()->brWindow.CreateSolidBrush(GetGlobalData()->clrWindow);

		GetGlobalData()->penHilite.DeleteObject();
		GetGlobalData()->penHilite.CreatePen(PS_SOLID, 1, GetGlobalData()->clrHilite);

		GetGlobalData()->penBarFace.DeleteObject();
		GetGlobalData()->penBarFace.CreatePen(PS_SOLID, 1, GetGlobalData()->clrBarFace);

		GetGlobalData()->penBarShadow.DeleteObject();
		GetGlobalData()->penBarShadow.CreatePen(PS_SOLID, 1, GetGlobalData()->clrBarShadow);

		// Windows 10 ribbon color
		m_clrWindows10Bar = RGB(31, 31, 31);

		m_clrGroupText = RGB(255, 255, 255);
		m_clrTabTextActive = RGB(255, 255, 255);
	}
	virtual void OnFillRibbonEdit(
		CDC* pDC,
		CMFCRibbonRichEditCtrl* pEdit,
		CRect rect,
		BOOL bIsHighlighted,
		BOOL bIsPaneHighlighted,
		BOOL bIsDisabled,
		COLORREF& clrText,
		COLORREF& clrSelBackground,
		COLORREF& clrSelText
	) {
		clrText = RGB(255, 255, 255);
		clrSelText = RGB(255, 255, 255);
		clrSelBackground = GetGlobalData()->clrActiveBorder;
	}

	virtual void GetSmartDockingBaseGuideColors(
		COLORREF& clrBaseGroupBackground,
		COLORREF& clrBaseGroupBorder
	) {
		COLORREF temp;
		CMFCVisualManagerOffice2007::GetSmartDockingBaseGuideColors(temp, clrBaseGroupBorder);
		clrBaseGroupBackground = 0xFFFFFF;
	}

	virtual COLORREF GetHighlightedMenuItemTextColor(CMFCToolBarMenuButton* pButton)
	{
		return RGB(255, 255, 255);
	}

	virtual void OnDrawRibbonApplicationButton(CDC* pDC, CMFCRibbonButton* pButton)
	{
		CMFCVisualManagerOffice2007::OnDrawRibbonApplicationButton(pDC, pButton);
	}

	virtual void OnDrawDefaultRibbonImage(CDC* pDC, CRect rectImage, BOOL bIsDisabled, BOOL bIsPressed, BOOL bIsHighlighted)
	{
		static_cast<void>(pDC);
		static_cast<void>(rectImage);
		static_cast<void>(bIsDisabled);
		static_cast<void>(bIsPressed);
		static_cast<void>(bIsHighlighted);
		return;
	}

	virtual void OnFillRibbonQuickAccessToolBarPopup(CDC* pDC, CMFCRibbonPanelMenuBar* pMenuBar, CRect rect)
	{
		static_cast<void>(pMenuBar);
		pDC->FillSolidRect(rect, RGB(255, 0, 0));
	}

public:
	virtual BOOL IsToolbarRoundShape(CMFCToolBar* pToolBar) override
	{
		static_cast<void>(pToolBar);
		return FALSE;
	}

	virtual void OnDrawHeaderCtrlBorder(CMFCHeaderCtrl* pCtrl, CDC* pDC, CRect& rect, BOOL bIsPressed, BOOL bIsHighlighted)
	{
		pDC->FillSolidRect(rect, GetGlobalData()->clrWindow);

		CPen pen(PS_SOLID, 1, GetGlobalData()->clrWindowFrame);
		pDC->SelectObject(pen);

		pDC->MoveTo(CPoint(rect.left, rect.bottom - 1));
		pDC->LineTo(CPoint(rect.right - 1, rect.bottom - 1));
		pDC->MoveTo(CPoint(rect.left, rect.top + 1));
		pDC->LineTo(CPoint(rect.right - 1, rect.top + 1));
		pDC->MoveTo(CPoint(rect.left + 1, rect.top + 1));
		pDC->LineTo(CPoint(rect.left - 1, rect.bottom));
		pDC->MoveTo(CPoint(rect.right + 1, rect.top + 1));
		pDC->LineTo(CPoint(rect.right - 1, rect.bottom));
	}

private:
	CBrush m_tabFaceBrush;
	CBrush m_tabBlackBrush;

	COLORREF m_clrWindows10Bar;
	COLORREF m_clrWindows10ApplicationButton;
};