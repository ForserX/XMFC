#pragma once

class XRibbonCheckBox : public CMFCRibbonCheckBox
{
	DECLARE_DYNCREATE(XRibbonCheckBox)

public:

	XRibbonCheckBox();
	XRibbonCheckBox(UINT nID, LPCTSTR lpszText);
	virtual ~XRibbonCheckBox();

	void OnDraw(CDC* pDC) override;

	[[nodiscard]] CSize GetIntermediateSize(CDC* pDC) override;

};


