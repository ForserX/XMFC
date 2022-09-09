#pragma once
#include <afxribboncategory.h>

class XRibbonCategory :
    public CMFCRibbonCategory
{
    friend class XRibbonBar;

public:

    XRibbonCategory() = default;

    XRibbonCategory(CMFCRibbonBar* pParentRibbonBar, LPCTSTR lpszName, UINT uiSmallImagesResID,
        UINT uiLargeImagesResID, CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32)) :
        CMFCRibbonCategory(pParentRibbonBar, lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage) {};

    virtual CMFCRibbonPanel* AddPanel(LPCTSTR lpszPanelName, HICON hIcon, CRuntimeClass* pRTI = nullptr);

    bool IsGroup() const;
    void SetGroup(const std::string_view Name);
    CString GetGroupName() const;

protected:

    virtual void OnDraw(CDC* pDC);
    void CommonInit(CMFCRibbonBar* pParentRibbonBar = NULL, LPCTSTR lpszName = NULL,
        UINT uiSmallImagesResID = 0, UINT uiLargeImagesResID = 0, CSize sizeSmallImage = CSize(0, 0), CSize sizeLargeImage = CSize(0, 0));

private:
    bool bHaveGroup = false;
    std::string GroupName;
};

