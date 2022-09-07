#define MY_RADIO_BUTTON_DEFAULT_SIZE (afxGlobalData.GetRibbonImageScale() == 1. ? 12 : 16)

const int nTextMarginLeft = 4;
const int nTextMarginRight = 6;

class XRibbonRadioBox : public CMFCRibbonCheckBox
{
public:
	XRibbonRadioBox(UINT nID, LPCTSTR lpszText) : CMFCRibbonCheckBox(nID, lpszText) {}

	virtual void OnDraw(CDC* pDC);
};