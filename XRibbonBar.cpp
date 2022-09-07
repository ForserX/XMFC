#include "pch.h"
#include "XRibbonBar.h"
#include <afxribboninfo.h>
#include <afxribboninfoloader.h>
#include <afxribbonconstructor.h>
#include "XRibbonConstructor.h"

IMPLEMENT_DYNAMIC(XRibbonBar, CMFCRibbonBar)


BEGIN_MESSAGE_MAP(XRibbonBar, CMFCRibbonBar)
END_MESSAGE_MAP()

XRibbonBar::XRibbonBar(BOOL bReplaceFrameCaption /*= TRUE*/)
	: CMFCRibbonBar(bReplaceFrameCaption)
{

}

XRibbonBar::~XRibbonBar()
{

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

	return TRUE;
}

BOOL XRibbonBar::LoadFromResource(UINT uiXMLResID, LPCTSTR lpszResType /*= RT_RIBBON*/, HINSTANCE hInstance /*= NULL*/)
{
	return CMFCRibbonBar::LoadFromResource(uiXMLResID, lpszResType, hInstance);
}
