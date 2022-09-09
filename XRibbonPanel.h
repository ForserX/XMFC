#pragma once
#include <afxribbonpanel.h>

class XRibbonCategory;

class XRibbonPanel :
    public CMFCRibbonPanel
{
    friend class XRibbonCategory;
public:
    XRibbonPanel() = default;
    XRibbonPanel(LPCTSTR lpszName = NULL, HICON hIcon = NULL) :CMFCRibbonPanel(lpszName, hIcon) {};

    virtual ~XRibbonPanel() = default;

public:
    static void SetNextPaneID(UINT ID);

protected:
    void CommonInit(LPCTSTR lpszName = NULL, HICON hIcon = NULL);
    void SetAllParent(XRibbonCategory* pWnd);
    virtual void DoPaint(CDC* pDC);
};

