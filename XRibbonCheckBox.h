#pragma once

class XRibbonCheckBox : public CMFCRibbonCheckBox
{
	DECLARE_DYNCREATE(XRibbonCheckBox)

public:

	XRibbonCheckBox();
	XRibbonCheckBox(UINT nID, LPCTSTR lpszText);
	virtual ~XRibbonCheckBox();

	void OnDraw(CDC* pDC) override;

	[[nodiscard]] virtual CSize GetIntermediateSize(CDC* pDC) override;

};


