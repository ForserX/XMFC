#pragma once

class XButton :
    public CButton
{
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
};

