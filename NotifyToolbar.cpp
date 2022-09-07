#include "pch.h"
#include "NotifyToolbar.h"

void CNotifyToolbar::OnUpdateCmdUI(CFrameWnd*, BOOL bDisableIfNoHndler)
{
	CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
}