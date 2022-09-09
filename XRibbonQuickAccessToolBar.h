#pragma once
#include <afxribbonquickaccesstoolbar.h>
class XRibbonQuickAccessToolBar :
    public CMFCRibbonQuickAccessToolBar
{

public:
    virtual void OnDraw(CDC* pDC) override;
};

