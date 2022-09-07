#pragma once
#include <afxmdiframewndex.h>
class XMDIMainFrame :
    public CMDIFrameWndEx
{
	DECLARE_MESSAGE_MAP()

public:
	XMDIMainFrame() = default;
	virtual ~XMDIMainFrame() override = default;

protected:
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
};

