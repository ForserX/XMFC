#include "pch.h"
#include "XRibbonPanel.h"
#include "XRibbonCategory.h"

void XRibbonPanel::SetNextPaneID(UINT ID)
{
	CMFCRibbonPanel::m_nNextPanelID = ID;
}

void XRibbonPanel::CommonInit(LPCTSTR lpszName, HICON hIcon)
{
	CMFCRibbonPanel::CommonInit(lpszName, hIcon);
}

void XRibbonPanel::SetAllParent(XRibbonCategory* pWnd)
{
	m_pParent = pWnd;
#if 0
	m_btnLaunch.m_pParent = this;
	m_btnDefault.m_pParent = this;
#endif
}

void XRibbonPanel::DoPaint(CDC* pDC)
{
	CMFCRibbonPanel::DoPaint(pDC);
}
