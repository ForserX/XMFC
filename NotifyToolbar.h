#pragma once
#include <afxtoolbar.h>

class CNotifyToolbar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler);

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

