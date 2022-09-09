#pragma once
#include <afxribbonbar.h>

class XRibbonCaptionButton :
    public CMFCRibbonCaptionButton
{
public:
   virtual void OnDraw(CDC* pDC) override;
};

