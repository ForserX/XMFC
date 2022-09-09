#pragma once
#include "XRibbonCategory.h"

class XRibbonBar : public CMFCRibbonBar
{
    DECLARE_DYNAMIC(XRibbonBar)
	DECLARE_MESSAGE_MAP()

protected:
    std::unordered_map<std::string, size_t> GroupTabs;

public:
    XRibbonBar(BOOL bReplaceFrameCaption = TRUE);

    virtual ~XRibbonBar();

    XRibbonCategory* AddCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID,
        CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32), int nInsertAt = -1, CRuntimeClass* pRTI = NULL);

    XRibbonCategory* AddContextCategory(LPCTSTR lpszName, LPCTSTR lpszContextName, UINT uiContextID, AFX_RibbonCategoryColor clrContext,
        UINT uiSmallImagesResID, UINT uiLargeImagesResID, CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32), CRuntimeClass* pRTI = NULL);


    BOOL LoadFromResource(LPCTSTR lpszXMLResID, LPCTSTR lpszResType = RT_RIBBON, HINSTANCE hInstance = NULL) override;
	BOOL LoadFromResource(UINT uiXMLResID, LPCTSTR lpszResType = RT_RIBBON, HINSTANCE hInstance = NULL) override;

protected:
    afx_msg void OnPaint();
};

