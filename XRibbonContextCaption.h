#pragma once
#include <afxribbonbar.h>
class XRibbonContextCaption :
    public CMFCRibbonContextCaption
{
    friend class XRibbonBar;

public:
    XRibbonContextCaption() = default;
    XRibbonContextCaption(LPCTSTR lpszName, UINT uiID, AFX_RibbonCategoryColor clrContext) : CMFCRibbonContextCaption(lpszName, uiID, clrContext) {};
};

