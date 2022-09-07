#pragma once
class XComboBox: public CComboBox
{
public:
	XComboBox();

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	void SetDropDownHeight(int itemsToShow)
	{
		//Get rectangles
		CRect rctComboBox, rctDropDown;
		//Combo rect
		GetClientRect(&rctComboBox);
		//DropDownList rect
		GetDroppedControlRect(&rctDropDown);

		//Get Item height
		int itemHeight = GetItemHeight(-1);
		//Converts coordinates
		GetParent()->ScreenToClient(&rctDropDown);
		//Set height
		rctDropDown.bottom = rctDropDown.top + rctComboBox.Height() + itemHeight * itemsToShow;
		//apply changes
		MoveWindow(&rctDropDown);
	}

protected:
	DECLARE_MESSAGE_MAP()
};