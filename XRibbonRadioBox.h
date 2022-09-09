#define MY_RADIO_BUTTON_DEFAULT_SIZE (afxGlobalData.GetRibbonImageScale() == 1. ? 12 : 16)

const int nTextMarginLeft = 4;
const int nTextMarginRight = 6;

class XRibbonRadioBox : public CMFCRibbonCheckBox
{
	size_t GroupID;

public:
	XRibbonRadioBox(UINT nID, LPCTSTR lpszText) : CMFCRibbonCheckBox(nID, lpszText), GroupID(-1) {}

	virtual void OnDraw(CDC* pDC);

public:
	size_t GetGroupID() const { return GroupID; };
	void   SetGroupID(size_t ID) noexcept { GroupID = ID; };

	void SetCheck(bool bVal);
};

class XRibbonRBManager
{
	std::vector<XRibbonRadioBox*> List;

public:
	constexpr XRibbonRBManager() = default;

	void SetCheck(size_t ID);
	void Emplace(XRibbonRadioBox* &RibbonRB) noexcept;
};

extern XRibbonRBManager* gRibonRBManager;