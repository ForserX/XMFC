#include "pch.h"
#include "XMDIMainFrame.h"

BEGIN_MESSAGE_MAP(XMDIMainFrame, CMDIFrameWndEx)
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()

void XMDIMainFrame::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CMDIFrameWndEx::OnWindowPosChanged(lpwndpos);

	HMONITOR Monitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);

	if (MainWnd)
	{
		MainWnd->SetMonitor(Monitor);
	}
}