#include "pch.h"
#include "PropWnd.h"

static long ID_GROUP_START = 8810;
static long ID_GROUP_BH_START = 7110;

BEGIN_MESSAGE_MAP(XPropGroup, XStatic)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_GROUP_BH_START, ID_GROUP_START - 1, BtnHideClick)
END_MESSAGE_MAP()

BOOL XPropGroup::Create(const RECT& rect, CWnd* pParentWnd, UINT nID, const char* GroupName)
{
	constexpr DWORD dwViewStyle = WS_CHILD | WS_VISIBLE;
	XStatic::Create("", dwViewStyle, rect, pParentWnd, nID);
	SetMode(true);

	CurrentFont.CreateFontA(BaseHeight, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Calibri"));

	HeaderText.Create(GroupName, dwViewStyle | SS_CENTER, rect, this, ID_GROUP_START++);
	HeaderText.SetMode(true);
	HeaderText.SetFont(&CurrentFont);

	RightBar.Create("", dwViewStyle | SS_CENTER, rect, this, ID_GROUP_START++);
	RightBar.SetMode(true);

	BtnID = ID_GROUP_BH_START++;
	HideBtn.Create("-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect, this, BtnID);

	return true;
}

void XPropGroup::BtnHideClick(UINT uID)
{
	if (BtnID == uID)
	{
		bVisible = !bVisible;

		HideBtn.SetWindowTextA(bVisible ? "-" : "+");

		// Make resize
		CRect ClientRect, Rect, RectParent;

		CWnd* Parent = GetParent();
		while (!dynamic_cast<XPropWnd*>(Parent))
		{
			Parent = Parent->GetParent();
		};

		XPropWnd* ParentProp = dynamic_cast<XPropWnd*>(Parent);
		if (ParentProp)
		{
			ParentProp->OnSize(0, 0, 0);
		}
	}
}

XPropGroup* XPropGroup::AddGroup(const char* GroupName)
{
	XPropGroup* Prop = (XPropGroup*)PropList.emplace_back(new XPropGroup);
	Prop->Create({ 0, 0, 100, BaseHeight }, this, ID_GROUP_START++, GroupName);
	return Prop;
}

XPropGroup* XPropGroup::GetGroup(const char* GroupName)
{
	for (XPropCtrl* Prop : PropList)
	{
		XPropGroup* TryGroup = dynamic_cast<XPropGroup*>(Prop);
		if (TryGroup != nullptr)
		{
			CString WndName = {};
			TryGroup->HeaderText.GetWindowTextA(WndName);

			if (WndName == GroupName)
				return TryGroup;
		}
	}

	return AddGroup(GroupName);
}

XPropGroup::~XPropGroup()
{
	for (XPropCtrl* Ctrl : PropList)
	{
		delete(Ctrl);
	}
}

XPropCtrlText* XPropGroup::AddText(const char* Name, std::string& Value)
{
	XPropCtrlText* TextCrtl = (XPropCtrlText*)PropList.emplace_back(new XPropCtrlText);
	TextCrtl->SetStr(Value);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}

XPropCtrlComboBox* XPropGroup::AddCombo(const char* Name, const std::string& List, std::string& Iterator)
{
	XPropCtrlComboBox* TextCrtl = (XPropCtrlComboBox*)PropList.emplace_back(new XPropCtrlComboBox);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name, List);

	return TextCrtl;
}

XPropCtrlNumeric* XPropGroup::AddNumeric(const char* Name, int& Iterator)
{
	XPropCtrlNumeric* TextCrtl = (XPropCtrlNumeric*)PropList.emplace_back(new XPropCtrlNumeric);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}

XPropCtrlNumericFloat* XPropGroup::AddNumeric(const char* Name, float& Iterator)
{
	XPropCtrlNumericFloat* TextCrtl = (XPropCtrlNumericFloat*)PropList.emplace_back(new XPropCtrlNumericFloat);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}

XPropCtrlNumericU32* XPropGroup::AddNumeric(const char* Name, unsigned int& Iterator)
{
	XPropCtrlNumericU32* TextCrtl = (XPropCtrlNumericU32*)PropList.emplace_back(new XPropCtrlNumericU32);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}

XPropCtrlNumericU16* XPropGroup::AddNumeric(const char* Name, std::uint16_t& Iterator)
{
	XPropCtrlNumericU16* TextCrtl = (XPropCtrlNumericU16*)PropList.emplace_back(new XPropCtrlNumericU16);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}

XPropCtrlNumericU8* XPropGroup::AddNumeric(const char* Name, std::uint8_t& Iterator)
{
	XPropCtrlNumericU8* TextCrtl = (XPropCtrlNumericU8*)PropList.emplace_back(new XPropCtrlNumericU8);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);
	
	return TextCrtl;
}

XPropCtrlNumericS16* XPropGroup::AddNumeric(const char* Name, std::int16_t& Iterator)
{
	XPropCtrlNumericS16* TextCrtl = (XPropCtrlNumericS16*)PropList.emplace_back(new XPropCtrlNumericS16);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}

XPropCtrlNumericS8* XPropGroup::AddNumeric(const char* Name, std::int8_t& Iterator)
{
	XPropCtrlNumericS8* TextCrtl = (XPropCtrlNumericS8*)PropList.emplace_back(new XPropCtrlNumericS8);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}

XPropCtrlCheck* XPropGroup::AddBool(const char* Name, bool& Iterator)
{
	XPropCtrlCheck* TextCrtl = (XPropCtrlCheck*)PropList.emplace_back(new XPropCtrlCheck);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}

void XPropGroup::AddButton(const char* Name, const char* ButtonName, std::function<void()> Ref)
{
	XPropCtrlButton* ButtonCrtl = (XPropCtrlButton*)PropList.emplace_back(new XPropCtrlButton);
	ButtonCrtl->SetValue(Ref);
	ButtonCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name, ButtonName);
}

void XPropGroup::AddButton2(const char* Name, const char* ButtonName1, std::function<void()> Ref1, const char* ButtonName2, std::function<void()> Ref2)
{
	XPropCtrlButton2* ButtonCrtl = (XPropCtrlButton2*)PropList.emplace_back(new XPropCtrlButton2);
	ButtonCrtl->SetValue(Ref1, Ref2);
	ButtonCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name, ButtonName1, ButtonName2);
}

void XPropGroup::AddButton3(const char* Name, const char* ButtonName1, std::function<void()> Ref1, const char* ButtonName2, std::function<void()> Ref2, const char* ButtonName3, std::function<void()> Ref3)
{
	XPropCtrlButton3* ButtonCrtl = (XPropCtrlButton3*)PropList.emplace_back(new XPropCtrlButton3);
	ButtonCrtl->SetValue(Ref1, Ref2, Ref3);
	ButtonCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name, ButtonName1, ButtonName2, ButtonName3);
}
#if 0
XPropCtrlNumericFV3* XPropGroup::AddFvector(const char* Name, Fvector& Iterator)
{
	XPropCtrlNumericFV3* TextCrtl = (XPropCtrlNumericFV3*)PropList.emplace_back(new XPropCtrlNumericFV3);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}

XPropCtrlNumericFV4* XPropGroup::AddFvector4(const char* Name, Fvector4& Iterator)
{
	XPropCtrlNumericFV4* TextCrtl = (XPropCtrlNumericFV4*)PropList.emplace_back(new XPropCtrlNumericFV4);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}
#endif
XPropCtrlColor* XPropGroup::AddColor(const char* Name, COLORREF& Iterator)
{
	XPropCtrlColor* TextCrtl = (XPropCtrlColor*)PropList.emplace_back(new XPropCtrlColor);
	TextCrtl->SetValue(Iterator);
	TextCrtl->Create({ 0, CalcCY() - BaseHeight, 100, CalcCY() }, this, Name);

	return TextCrtl;
}

int XPropGroup::CalcCY() const
{
	if (!Visible())
		return BaseHeight;

	long CY = BaseHeight;

	for (XPropCtrl* Ctrl : PropList)
	{
		XPropGroup* GroupPtr = dynamic_cast<XPropGroup*>(Ctrl);
		if (GroupPtr)
		{
			CY += GroupPtr->CalcCY();
		}
		else
		{
			CY += BaseHeight;
		}
	}
	return CY;
}

void XPropGroup::OnSize(UINT nType, int cx, int cy)
{
	CRect ClientRect;
	GetClientRect(ClientRect);

	long YOffset = ClientRect.top + BaseHeight;
	long XStartPos = 20;
	long XEndPos = ClientRect.right;
	long YEndPos = YOffset + BaseHeight;

	RightBar.SetWindowPos(nullptr, 0, ClientRect.top, 20, ClientRect.bottom, SWP_NOACTIVATE | SWP_NOZORDER);

	HideBtn.SetWindowPos(nullptr, 4, 4, 14, 14, SWP_NOACTIVATE | SWP_NOZORDER);
	HeaderText.SetWindowPos(nullptr, XStartPos, ClientRect.top, ClientRect.right, YOffset, SWP_NOACTIVATE | SWP_NOZORDER);

	if (!bVisible)
	{
		YOffset = XStartPos = XEndPos = YEndPos = 0;
	}

	for (XPropCtrl* Ctrl : PropList)
	{
		XPropCtrlBase* BaseCtrl = dynamic_cast<XPropCtrlBase*>(Ctrl);
		if (BaseCtrl)
		{
			BaseCtrl->SetWindowPos(nullptr, XStartPos, YOffset, XEndPos, YEndPos, SWP_NOACTIVATE | SWP_NOZORDER);

			if (bVisible)
			{
				YOffset = YEndPos;
				YEndPos += BaseHeight;
			}
		}
		else
		{
			XPropGroup* BaseCtrlGroup = dynamic_cast<XPropGroup*>(Ctrl);

			YEndPos += BaseCtrlGroup->CalcCY() - BaseHeight;
			BaseCtrlGroup->SetWindowPos(nullptr, XStartPos, YOffset, XEndPos, YEndPos, SWP_NOACTIVATE | SWP_NOZORDER);

			if (bVisible)
			{
				YOffset = YEndPos;
				YEndPos += BaseHeight;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// WND

BEGIN_MESSAGE_MAP(XPropWnd, XStatic)
	ON_WM_SIZE()
END_MESSAGE_MAP()

XPropWnd::XPropWnd()
{
	if (MainWnd)
	{
		MainWnd->OnMonitorChanged.emplace_back([this](HMONITOR InMonitor)
			{
				float DPIScaleFactorY = float(MainWnd->DPI.y) / 96.0f;
				float EffectiveScalingY = std::max(DPIScaleFactorY, MainWnd->ScaleFactor);
				BaseHeight = long((20.f * EffectiveScalingY) + 0.5f);
				OnSize(0, 0, 0);
			});
	}
	else
	{
		BaseHeight = 16;
	}
}

BOOL XPropWnd::Create(const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	constexpr DWORD dwViewStyle = WS_CHILD | WS_VISIBLE;
	SetMode(true);

	return XStatic::Create("", dwViewStyle, rect, pParentWnd, nID);
}

XPropGroup* XPropWnd::AddGroup(const char* GroupName)
{
	PropList[GroupName] = (new XPropGroup);
	PropList[GroupName]->Create({ 0, 0, 100, BaseHeight }, this, ID_GROUP_START++, GroupName);
	return PropList[GroupName];
}

XPropGroup* XPropWnd::GetGroup(const char* GroupName)
{
	if (!PropList[GroupName])
	{
		return AddGroup(GroupName);
	}

	return PropList[GroupName];
}

void XPropWnd::OnSize(UINT nType, int cx, int cy)
{
	long YOffset = 0;

	CRect ClientRect;
	GetClientRect(ClientRect);

	for (auto&[Name, Ctrl] : PropList)
	{
		Ctrl->SetWindowPos(nullptr, ClientRect.left, YOffset, ClientRect.right, YOffset + Ctrl->CalcCY(), SWP_NOACTIVATE | SWP_NOZORDER);
		YOffset += Ctrl->CalcCY();
	}
}
