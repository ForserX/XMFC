#pragma once

class XStatic : public CStatic
{
	bool bCaption = false;
	bool bFrame = false;

	DECLARE_MESSAGE_MAP()
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	
public:
	virtual BOOL Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
	void SetMode(bool Caption, bool Frame = false);
	void OnPaint();
};