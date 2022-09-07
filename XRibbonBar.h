#pragma once

class XRibbonBar : public CMFCRibbonBar
{

    DECLARE_DYNAMIC(XRibbonBar)

public:
    XRibbonBar(BOOL bReplaceFrameCaption = TRUE);

    virtual ~XRibbonBar();

    BOOL LoadFromResource(LPCTSTR lpszXMLResID, LPCTSTR lpszResType = RT_RIBBON, HINSTANCE hInstance = NULL) override;
	BOOL LoadFromResource(UINT uiXMLResID, LPCTSTR lpszResType = RT_RIBBON, HINSTANCE hInstance = NULL) override;

	DECLARE_MESSAGE_MAP()


public:

};

