#include "pch.h"
#include "PropCtrl.h"
#include <string_view>

// Valid types - std::string, xwstring
template <typename StringType>
struct StringOperations
{
	using CharType = typename StringType::value_type;

	static std::vector<StringType> Split(const StringType& InString, CharType SplitCh)
	{
		std::vector<StringType> Result;

		size_t SubStrBeginCursor = 0;
		size_t Len = 0;

		size_t StrCursor = 0;
		for (; StrCursor < InString.size(); ++StrCursor)
		{
			if (InString.at(StrCursor) == SplitCh)
			{
				if ((StrCursor - SubStrBeginCursor) > 0)
				{
					Len = StrCursor - SubStrBeginCursor;
					Result.emplace_back(StringType(&InString.at(SubStrBeginCursor), Len));
					SubStrBeginCursor = StrCursor + 1;
				}
				else
				{
					Result.emplace_back("");
					SubStrBeginCursor = StrCursor + 1;
				}
			}
		}

		if (StrCursor > SubStrBeginCursor)
		{
			Len = StrCursor - SubStrBeginCursor;
			Result.emplace_back(StringType(&InString.at(SubStrBeginCursor), Len));
		}
		return Result;
	}

	static std::vector<StringType> Split(StringType& InString, size_t NumberOfSplits, va_list args)
	{
		std::vector<StringType> intermediateTokens;
		std::vector<StringType> Result;

		for (size_t i = 0; i < NumberOfSplits; ++i)
		{
			CharType splitCh = va_arg(args, CharType);

			//special case for first try
			if (i == 0)
			{
				Result = StringOperations<StringType>::Split(InString, splitCh);
			}

			for (StringType& str : Result)
			{
				std::vector<StringType> TokenStrResult = str.Split(splitCh);
				intermediateTokens.insert(intermediateTokens.end(), TokenStrResult.begin(), TokenStrResult.end());
			}

			if (!intermediateTokens.empty())
			{
				Result.clear();
				Result.insert(Result.begin(), intermediateTokens.begin(), intermediateTokens.end());
				intermediateTokens.clear();
			}
		}

		return Result;
	}

	static constexpr CharType GetWhitespaceCharacter()
	{
		if constexpr (std::is_same_v<CharType, char>)
		{
			return ' ';
		}
		else if constexpr (std::is_same_v<CharType, wchar_t>)
		{
			return L' ';
		}
	}

	static StringType RemoveWhitespaces(const StringType& InString)
	{
		size_t Size = InString.size();
		if (Size == 0) return StringType();

		StringType Result;
		Result.reserve(Size);

		const CharType* OrigStr = InString.data();

		for (size_t i = 0; i < Size; ++i)
		{
			if (*OrigStr != GetWhitespaceCharacter())
			{
				Result.push_back(OrigStr[i]);
			}
		}

		return Result;
	}

	static bool StartWith(const StringType& InString, const CharType* Str, size_t Size)
	{
		size_t OurSize = InString.size();

		//String is greater then our, we can't success
		if (OurSize < Size) return false;

		const CharType* OurStr = InString.data();

		for (size_t i = 0; i < Size; ++i)
		{
			if (OurStr[i] != Str[i])
			{
				return false;
			}
		}

		return true;
	}
};

//std::string class
std::vector<std::string> Split(const std::string& str, char splitCh)
{
	return StringOperations<std::string>::Split(str, splitCh);
}

long BaseHeight = 20;
static unsigned int ID_PROPERTY_START = 44000;
constexpr DWORD dwViewStyle = WS_CHILD | WS_VISIBLE;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base Ctrl
BEGIN_MESSAGE_MAP(XPropCtrlBase, XStatic)
	ON_WM_SIZE()
	//	ON_WM_PAINT()
END_MESSAGE_MAP()

XPropCtrlBase::XPropCtrlBase()
{
	CurrentFont = new CFont;
	bCreated = false;
}

XPropCtrlBase::~XPropCtrlBase()
{
	delete(CurrentFont);
}

BOOL XPropCtrlBase::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XStatic::Create("", dwViewStyle, rect, pParentWnd, ID_PROPERTY_START++);

	CurrentFont->CreateFontA(BaseHeight - 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Calibri"));

	CRect NameRect = rect;
	NameRect.right /= 2;

	PropName.Create(Name, WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropName.SetFont(CurrentFont);
	PropName.SetMode(false, true);

	return true;
}

void XPropCtrlBase::OnSize(UINT nType, int cx, int cy)
{
	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect NameRect = ClientRect;
	NameRect.right /= 2;
	NameRect.right -= 15;

	PropName.SetWindowPos(nullptr, NameRect.left, NameRect.top, NameRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
}

void XPropCtrlBase::EditChange(UINT uID)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Text Ctrl
static unsigned int ID_PROPERTY_TEXT_START = 45000;

BEGIN_MESSAGE_MAP(XPropCtrlText, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(EN_CHANGE, ID_PROPERTY_TEXT_START, ID_PROPERTY_TEXT_START + 500, EditChange)
END_MESSAGE_MAP()

BOOL XPropCtrlText::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_TEXT_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetFont(CurrentFont);
	PropBack.SetMode(false, true);

	PropText.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, NameRect, this, PropID);
	PropText.SetWindowTextA((*LinkStr).c_str());
	PropText.SetFrameRender(false);
	PropText.SetFont(CurrentFont);

	bCreated = true;
	return 0;
}

void XPropCtrlText::EditChange(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropID && LinkStr)
	{
		CString Str;
		PropText.GetWindowTextA(Str);
		std::string CurSel = Str.operator LPCSTR();

		*LinkStr = CurSel;

		XPropCtrlBase::EditChange(uID);
	}
}

void XPropCtrlText::SetStr(std::string& RefStr)
{
	LinkStr = &RefStr;
}

void XPropCtrlText::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	PropText.SetWindowPos(nullptr, TextRect.left + 1, TextRect.top + 1, TextRect.right - 1, BaseHeight - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Combo Ctrl
static unsigned int ID_PROPERTY_COMBO_START = 45500;

BEGIN_MESSAGE_MAP(XPropCtrlComboBox, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(CBN_SELCHANGE, ID_PROPERTY_COMBO_START, ID_PROPERTY_COMBO_START + 500, EditChange)
END_MESSAGE_MAP()

BOOL XPropCtrlComboBox::Create(const RECT& rect, CWnd* pParentWnd, const char* Name, std::string List)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropComboID = ID_PROPERTY_COMBO_START++;
	PropCombo.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST, NameRect, this, PropComboID);

	PropCombo.SetFont(CurrentFont);
	PropCombo.SetItemHeight(-1, 18);
	ValList = Split(List, '|');

	auto Iter = std::find(ValList.begin(), ValList.end(), std::string((*LinkIter).c_str()));

	for (std::string& Token : ValList)
	{
		PropCombo.AddString(StrDupA(Token.c_str()));
	}
	PropCombo.SetCurSel(std::distance(ValList.begin(), Iter));
	PropCombo.SetDropDownHeight(5);

	bCreated = true;

	return true;
}

void XPropCtrlComboBox::SetValue(std::string& RefIter)
{
	LinkIter = &RefIter;
}

void XPropCtrlComboBox::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	PropCombo.GetClientRect(ClientRect);

	PropCombo.SetWindowPos(nullptr, TextRect.left, TextRect.top, -17 + (TextRect.right / 2), BaseHeight - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void XPropCtrlComboBox::EditChange(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropComboID && LinkIter)
	{
		int CurSel = PropCombo.GetCurSel();
		std::string TempStr = ValList[CurSel].c_str();

		*LinkIter = std::move(TempStr);

		XPropCtrlBase::EditChange(uID);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric ctrl
static unsigned int ID_PROPERTY_NUMERIC_START = 46000;

BEGIN_MESSAGE_MAP(XPropCtrlNumeric, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(EN_CHANGE, ID_PROPERTY_NUMERIC_START, ID_PROPERTY_NUMERIC_START + 500, EditChange)
END_MESSAGE_MAP()


BOOL XPropCtrlNumeric::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_NUMERIC_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetFont(CurrentFont);
	PropBack.SetMode(false, true);

	PropText.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_NUMBER, NameRect, this, PropID);
	PropText.SetWindowTextA(std::to_string(*LinkVal).c_str());
	PropText.SetFrameRender(false);
	PropText.SetFont(CurrentFont);

	bCreated = true;

	return 0;
}

void XPropCtrlNumeric::EditChange(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropID && LinkVal)
	{
		CString Str;
		PropText.GetWindowTextA(Str);

		int NewVal = atoi(Str.operator LPCSTR());

		*LinkVal = NewVal;

		XPropCtrlBase::EditChange(uID);
	}
}

void XPropCtrlNumeric::SetValue(int& RefStr)
{
	LinkVal = &RefStr;
}

void XPropCtrlNumeric::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	PropText.SetWindowPos(nullptr, TextRect.left + 1, TextRect.top + 1, TextRect.right - 1, BaseHeight - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric float ctrl
static unsigned int ID_PROPERTY_NUMERICF_START = 46500;

BEGIN_MESSAGE_MAP(XPropCtrlNumericFloat, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(EN_CHANGE, ID_PROPERTY_NUMERICF_START, ID_PROPERTY_NUMERICF_START + 500, EditChange)
END_MESSAGE_MAP()


BOOL XPropCtrlNumericFloat::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_NUMERICF_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetFont(CurrentFont);
	PropBack.SetMode(false, true);

	PropText.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, NameRect, this, PropID);
	float& CurFlt = *LinkVal;

	PropText.SetWindowTextA(std::to_string(CurFlt).substr(0, 4).c_str());
	PropText.SetFrameRender(false);
	PropText.SetFont(CurrentFont);

	bCreated = true;

	return 0;
}

void XPropCtrlNumericFloat::EditChange(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropID && LinkVal)
	{
		CString Str;
		PropText.GetWindowTextA(Str);

		float NewVal = (float)atof(Str.operator LPCSTR());

		*LinkVal = NewVal;

		XPropCtrlBase::EditChange(uID);
	}
}

void XPropCtrlNumericFloat::SetValue(float& RefStr)
{
	LinkVal = &RefStr;
}

void XPropCtrlNumericFloat::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	PropText.SetWindowPos(nullptr, TextRect.left + 1, TextRect.top + 1, TextRect.right - 1, BaseHeight - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Checkbox
static unsigned int ID_PROPERTY_BOOL_START = 47000;

BEGIN_MESSAGE_MAP(XPropCtrlCheck, XStatic)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_PROPERTY_BOOL_START, ID_PROPERTY_BOOL_START + 500, EditChange)
END_MESSAGE_MAP()


BOOL XPropCtrlCheck::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_BOOL_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetMode(false, true);

	Box.Create(*LinkVal, this, PropID);
	bCreated = true;

	return 0;
}

void XPropCtrlCheck::EditChange(UINT uID)
{
	if (!bCreated)
		return;

	bool bCheck = Box.GetCheck();

	if (uID == PropID && LinkVal)
	{
		*LinkVal = bCheck;

		XPropCtrlBase::EditChange(uID);
	}
}

void XPropCtrlCheck::SetValue(bool& RefStr)
{
	LinkVal = &RefStr;
}

void XPropCtrlCheck::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	Box.SetWindowPos(nullptr, TextRect.left + 5, TextRect.top + 6, 15, 17, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Button
static unsigned int ID_PROPERTY_BUTTON_START = 47500;

BEGIN_MESSAGE_MAP(XPropCtrlButton, XStatic)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_PROPERTY_BUTTON_START, ID_PROPERTY_BUTTON_START + 500, ButtonPush)
END_MESSAGE_MAP()


BOOL XPropCtrlButton::Create(const RECT& rect, CWnd* pParentWnd, const char* Name, const char* ButtonName)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_BUTTON_START++;

	CRect BtnRect = rect;
	BtnRect.left = BtnRect.right / 2;
	Button.Create(ButtonName, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, BtnRect, this, PropID);

	bCreated = true;
	return 0;
}

void XPropCtrlButton::ButtonPush(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropID && LinkVal)
	{
		LinkVal();
	}
}

void XPropCtrlButton::SetValue(std::function<void()> RefValue)
{
	LinkVal = RefValue;
}

void XPropCtrlButton::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect ButtonRect = ClientRect;
	ButtonRect.left = ButtonRect.right / 2;
	ButtonRect.left -= 15;

	Button.SetWindowPos(nullptr, ButtonRect.left + 1, ButtonRect.top, ButtonRect.Width() - 20, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Button2
static unsigned int ID_PROPERTY_BUTTON2_START = 48000;

BEGIN_MESSAGE_MAP(XPropCtrlButton2, XStatic)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_PROPERTY_BUTTON2_START, ID_PROPERTY_BUTTON2_START + 500, ButtonPush)
END_MESSAGE_MAP()

BOOL XPropCtrlButton2::Create(const RECT& rect, CWnd* pParentWnd, const char* Name, const char* ButtonName1, const char* ButtonName2)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropButton1ID = ID_PROPERTY_BUTTON2_START++;
	PropButton2ID = ID_PROPERTY_BUTTON2_START++;

	CRect BtnRect = rect;
	BtnRect.left = BtnRect.right / 2;

	Button1.Create(ButtonName1, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, BtnRect, this, PropButton1ID);
	Button2.Create(ButtonName2, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, BtnRect, this, PropButton2ID);

	bCreated = true;

	return 0;
}

void XPropCtrlButton2::ButtonPush(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropButton1ID && LinkVal1)
	{
		LinkVal1();
	}
	else if (uID == PropButton2ID && LinkVal2)
	{
		LinkVal2();
	}
}

void XPropCtrlButton2::SetValue(std::function<void()> RefValue1, std::function<void()> RefValue2)
{
	LinkVal1 = RefValue1;
	LinkVal2 = RefValue2;
}

void XPropCtrlButton2::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect ButtonRect = ClientRect;
	ButtonRect.left = ButtonRect.right / 2;
	ButtonRect.left -= 15;

	long offset = (ButtonRect.left / 2) + 9;

	Button1.SetWindowPos(nullptr, ButtonRect.left + 1, ButtonRect.top, offset, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	Button2.SetWindowPos(nullptr, ButtonRect.left + 1 + offset, ButtonRect.top, offset, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Button3
static unsigned int ID_PROPERTY_BUTTON3_START = 48500;

BEGIN_MESSAGE_MAP(XPropCtrlButton3, XStatic)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_PROPERTY_BUTTON3_START, ID_PROPERTY_BUTTON3_START + 500, ButtonPush)
END_MESSAGE_MAP()

BOOL XPropCtrlButton3::Create(const RECT& rect, CWnd* pParentWnd, const char* Name, const char* ButtonName1, const char* ButtonName2, const char* ButtonName3)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropButton1ID = ID_PROPERTY_BUTTON3_START++;
	PropButton2ID = ID_PROPERTY_BUTTON3_START++;
	PropButton3ID = ID_PROPERTY_BUTTON3_START++;

	CRect BtnRect = rect;
	BtnRect.left = BtnRect.right / 3;

	Button1.Create(ButtonName1, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, BtnRect, this, PropButton1ID);
	Button2.Create(ButtonName2, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, BtnRect, this, PropButton2ID);
	Button3.Create(ButtonName3, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, BtnRect, this, PropButton3ID);

	bCreated = true;

	return 0;
}

void XPropCtrlButton3::ButtonPush(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropButton1ID && LinkVal1)
	{
		LinkVal1();
	}
	else if (uID == PropButton2ID && LinkVal2)
	{
		LinkVal2();
	}
	else if (uID == PropButton3ID && LinkVal3)
	{
		LinkVal3();
	}
}

void XPropCtrlButton3::SetValue(std::function<void()> RefValue1, std::function<void()> RefValue2, std::function<void()> RefValue3)
{
	LinkVal1 = RefValue1;
	LinkVal2 = RefValue2;
	LinkVal3 = RefValue3;
}

void XPropCtrlButton3::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect ButtonRect1 = ClientRect;
	ButtonRect1.left = ButtonRect1.right / 2;
	ButtonRect1.left -= 15;

	long offset = (ButtonRect1.left / 3) + 5;

	CRect ButtonRect2 = ClientRect;
	ButtonRect2.left = ButtonRect1.left + offset;

	CRect ButtonRect3 = ClientRect;
	ButtonRect3.left = ButtonRect2.left + offset;

	Button1.SetWindowPos(nullptr, ButtonRect1.left + 1, 0, offset, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	Button2.SetWindowPos(nullptr, ButtonRect2.left + 1, 0, offset, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	Button3.SetWindowPos(nullptr, ButtonRect3.left + 1, 0, offset, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
}
#if 0
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric float vector ctrl
static unsigned int ID_PROPERTY_NUMERICFV3_START = 49000;

BEGIN_MESSAGE_MAP(XPropCtrlNumericFV3, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(EN_CHANGE, ID_PROPERTY_NUMERICFV3_START, ID_PROPERTY_NUMERICFV3_START + 500, EditChange)
END_MESSAGE_MAP()


BOOL XPropCtrlNumericFV3::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	FVID[0] = ID_PROPERTY_NUMERICFV3_START++;
	FVID[1] = ID_PROPERTY_NUMERICFV3_START++;
	FVID[2] = ID_PROPERTY_NUMERICFV3_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetFont(CurrentFont);
	PropBack.SetMode(true, true);

	PropX.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, NameRect, this, FVID[0]);
	PropX.SetWindowTextA(std::to_string(LinkVal->x).substr(0, 4).c_str());
	PropX.SetFrameRender(false);
	PropX.SetFont(CurrentFont);

	PropY.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, NameRect, this, FVID[1]);
	PropY.SetWindowTextA(std::to_string(LinkVal->y).substr(0, 4).c_str());
	PropY.SetFrameRender(false);
	PropY.SetFont(CurrentFont);

	PropZ.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, NameRect, this, FVID[2]);
	PropZ.SetWindowTextA(std::to_string(LinkVal->z).substr(0, 4).c_str());
	PropZ.SetFrameRender(false);
	PropZ.SetFont(CurrentFont);

	bCreated = true;

	return 0;
}

void XPropCtrlNumericFV3::EditChange(UINT uID)
{
	if (!bCreated || !LinkVal)
		return;

	if (uID == FVID[0])
	{
		CString Str;
		PropX.GetWindowTextA(Str);

		(*LinkVal).x = (float)atof(Str.operator LPCSTR());
	}
	else if (uID == FVID[1])
	{
		CString Str;
		PropY.GetWindowTextA(Str);

		(*LinkVal).y = (float)atof(Str.operator LPCSTR());
	}
	else if (uID == FVID[2])
	{
		CString Str;
		PropZ.GetWindowTextA(Str);

		(*LinkVal).z = (float)atof(Str.operator LPCSTR());
	}

}

void XPropCtrlNumericFV3::SetValue(Fvector& RefStr)
{
	LinkVal = &RefStr;
}

void XPropCtrlNumericFV3::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	long offset = long(float(TextRect.left) / 3.f + 0.5f);
	offset += 5;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);

	PropX.SetWindowPos(nullptr, TextRect.left + 1, TextRect.top + 1, offset - 1, BaseHeight - 1, SWP_NOACTIVATE | SWP_NOZORDER);
	PropY.SetWindowPos(nullptr, TextRect.left + offset + 1, TextRect.top + 1, offset - 1, BaseHeight - 1, SWP_NOACTIVATE | SWP_NOZORDER);
	PropZ.SetWindowPos(nullptr, TextRect.left + offset + offset + 1, TextRect.top + 1, offset - 1, BaseHeight - 1, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric float vector ctrl
static unsigned int ID_PROPERTY_NUMERICFV4_START = 49500;

BEGIN_MESSAGE_MAP(XPropCtrlNumericFV4, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(EN_CHANGE, ID_PROPERTY_NUMERICFV3_START, ID_PROPERTY_NUMERICFV3_START + 500, EditChange)
END_MESSAGE_MAP()


BOOL XPropCtrlNumericFV4::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	FVID[0] = ID_PROPERTY_NUMERICFV3_START++;
	FVID[1] = ID_PROPERTY_NUMERICFV3_START++;
	FVID[2] = ID_PROPERTY_NUMERICFV3_START++;
	FVID[3] = ID_PROPERTY_NUMERICFV3_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetFont(CurrentFont);
	PropBack.SetMode(true, true);

	PropX.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, NameRect, this, FVID[0]);
	PropX.SetWindowTextA(std::to_string(LinkVal->x).substr(0, 4).c_str());
	PropX.SetFrameRender(false);
	PropX.SetFont(CurrentFont);

	PropY.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, NameRect, this, FVID[1]);
	PropY.SetWindowTextA(std::to_string(LinkVal->y).substr(0, 4).c_str());
	PropY.SetFrameRender(false);
	PropY.SetFont(CurrentFont);

	PropZ.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, NameRect, this, FVID[2]);
	PropZ.SetWindowTextA(std::to_string(LinkVal->z).substr(0, 4).c_str());
	PropZ.SetFrameRender(false);
	PropZ.SetFont(CurrentFont);

	PropW.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, NameRect, this, FVID[3]);
	PropW.SetWindowTextA(std::to_string(LinkVal->w).substr(0, 4).c_str());
	PropW.SetFrameRender(false);
	PropW.SetFont(CurrentFont);

	bCreated = true;

	return 0;
}

void XPropCtrlNumericFV4::EditChange(UINT uID)
{
	if (!bCreated || !LinkVal)
		return;

	if (uID == FVID[0])
	{
		CString Str;
		PropX.GetWindowTextA(Str);

		(*LinkVal).x = (float)atof(Str.operator LPCSTR());
	}
	else if (uID == FVID[1])
	{
		CString Str;
		PropY.GetWindowTextA(Str);

		(*LinkVal).y = (float)atof(Str.operator LPCSTR());
	}
	else if (uID == FVID[2])
	{
		CString Str;
		PropZ.GetWindowTextA(Str);

		(*LinkVal).z = (float)atof(Str.operator LPCSTR());
	}
	else if (uID == FVID[3])
	{
		CString Str;
		PropW.GetWindowTextA(Str);

		(*LinkVal).w = (float)atof(Str.operator LPCSTR());
	}
}

void XPropCtrlNumericFV4::SetValue(Fvector4& RefStr)
{
	LinkVal = &RefStr;
}

void XPropCtrlNumericFV4::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	long offset = long(float(TextRect.left) / 4.f + 0.5f);
	offset += 3;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);

	PropX.SetWindowPos(nullptr, TextRect.left + 1, TextRect.top + 1, offset - 1, BaseHeight - 1, SWP_NOACTIVATE | SWP_NOZORDER);
	PropY.SetWindowPos(nullptr, TextRect.left + offset + 1, TextRect.top + 1, offset - 1, BaseHeight - 1, SWP_NOACTIVATE | SWP_NOZORDER);
	PropZ.SetWindowPos(nullptr, TextRect.left + offset + offset + 1, TextRect.top + 1, offset - 1, BaseHeight - 1, SWP_NOACTIVATE | SWP_NOZORDER);
	PropW.SetWindowPos(nullptr, TextRect.left + offset + offset + offset + 1, TextRect.top + 1, offset - 1, BaseHeight - 1, SWP_NOACTIVATE | SWP_NOZORDER);
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Button
static unsigned int ID_PROPERTY_BUTTON_CLR_START = 50000;

BEGIN_MESSAGE_MAP(XPropCtrlColor, XStatic)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_PROPERTY_BUTTON_CLR_START, ID_PROPERTY_BUTTON_CLR_START + 500, ButtonPush)
END_MESSAGE_MAP()


BOOL XPropCtrlColor::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_BUTTON_CLR_START++;

	CRect BtnRect = rect;
	BtnRect.left = BtnRect.right / 2;
	ClrButton.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP, BtnRect, this, PropID);
	ClrButton.SetColor(*LinkVal);
	ClrButton.EnableOtherButton("More...");
	ClrButton.m_bEnabledInCustomizeMode = true;

	bCreated = true;
	return 0;
}

void XPropCtrlColor::ButtonPush(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropID && LinkVal)
	{
		*LinkVal = ClrButton.GetColor();
	}
}

void XPropCtrlColor::SetValue(COLORREF& RefValue)
{
	LinkVal = &RefValue;
}

void XPropCtrlColor::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect ButtonRect = ClientRect;
	ButtonRect.left = ButtonRect.right / 2;
	ButtonRect.left -= 15;

	ClrButton.SetWindowPos(nullptr, ButtonRect.left + 1, ButtonRect.top, ButtonRect.Width() - 20, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric ctrl
static unsigned int ID_PROPERTY_NUMERICU32_START = 50500;

BEGIN_MESSAGE_MAP(XPropCtrlNumericU32, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(EN_CHANGE, ID_PROPERTY_NUMERICU32_START, ID_PROPERTY_NUMERICU32_START + 500, EditChange)
END_MESSAGE_MAP()


BOOL XPropCtrlNumericU32::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_NUMERICU32_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetFont(CurrentFont);
	PropBack.SetMode(false, true);

	PropText.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, NameRect, this, PropID);
	PropText.SetWindowTextA(std::to_string(*LinkVal).c_str());
	PropText.SetFrameRender(false);
	PropText.SetFont(CurrentFont);

	bCreated = true;

	return 0;
}

void XPropCtrlNumericU32::EditChange(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropID && LinkVal)
	{
		CString Str;
		PropText.GetWindowTextA(Str);

		unsigned int NewVal = (unsigned int)atoll(Str.operator LPCSTR());

		*LinkVal = NewVal;

		XPropCtrlBase::EditChange(uID);
	}
}

void XPropCtrlNumericU32::SetValue(unsigned int& RefStr)
{
	LinkVal = &RefStr;
}

void XPropCtrlNumericU32::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	PropText.SetWindowPos(nullptr, TextRect.left + 1, TextRect.top + 1, TextRect.right - 1, BaseHeight - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric ctrl
static unsigned int ID_PROPERTY_NUMERICU16_START = 51000;

BEGIN_MESSAGE_MAP(XPropCtrlNumericU16, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(EN_CHANGE, ID_PROPERTY_NUMERICU16_START, ID_PROPERTY_NUMERICU16_START + 500, EditChange)
END_MESSAGE_MAP()


BOOL XPropCtrlNumericU16::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_NUMERICU16_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetFont(CurrentFont);
	PropBack.SetMode(false, true);

	PropText.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_NUMBER, NameRect, this, PropID);
	PropText.SetWindowTextA(std::to_string(*LinkVal).c_str());
	PropText.SetFrameRender(false);
	PropText.SetFont(CurrentFont);

	bCreated = true;

	return 0;
}

void XPropCtrlNumericU16::EditChange(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropID && LinkVal)
	{
		CString Str;
		PropText.GetWindowTextA(Str);

		std::uint16_t NewVal = (unsigned int)atoll(Str.operator LPCSTR());

		*LinkVal = NewVal;

		XPropCtrlBase::EditChange(uID);
	}
}

void XPropCtrlNumericU16::SetValue(std::uint16_t& RefStr)
{
	LinkVal = &RefStr;
}

void XPropCtrlNumericU16::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	PropText.SetWindowPos(nullptr, TextRect.left + 1, TextRect.top + 1, TextRect.right - 1, BaseHeight - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric ctrl
static unsigned int ID_PROPERTY_NUMERIC_S8_START = 52000;

BEGIN_MESSAGE_MAP(XPropCtrlNumericS8, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(EN_CHANGE, ID_PROPERTY_NUMERIC_S8_START, ID_PROPERTY_NUMERIC_S8_START + 500, EditChange)
END_MESSAGE_MAP()


BOOL XPropCtrlNumericS8::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_NUMERIC_S8_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetFont(CurrentFont);
	PropBack.SetMode(false, true);

	PropText.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_NUMBER, NameRect, this, PropID);
	PropText.SetWindowTextA(std::to_string(*LinkVal).c_str());
	PropText.SetFrameRender(false);
	PropText.SetFont(CurrentFont);

	bCreated = true;

	return 0;
}

void XPropCtrlNumericS8::EditChange(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropID && LinkVal)
	{
		CString Str;
		PropText.GetWindowTextA(Str);

		std::int8_t NewVal = (std::int8_t)atoi(Str.operator LPCSTR());

		*LinkVal = NewVal;

		XPropCtrlBase::EditChange(uID);
	}
}

void XPropCtrlNumericS8::SetValue(std::int8_t& RefStr)
{
	LinkVal = &RefStr;
}

void XPropCtrlNumericS8::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	PropText.SetWindowPos(nullptr, TextRect.left + 1, TextRect.top + 1, TextRect.right - 1, BaseHeight - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric ctrl
static unsigned int ID_PROPERTY_NUMERICU8_START = 51500;

BEGIN_MESSAGE_MAP(XPropCtrlNumericU8, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(EN_CHANGE, ID_PROPERTY_NUMERICU8_START, ID_PROPERTY_NUMERICU8_START + 500, EditChange)
END_MESSAGE_MAP()


BOOL XPropCtrlNumericU8::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_NUMERICU8_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetFont(CurrentFont);
	PropBack.SetMode(false, true);

	PropText.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_NUMBER, NameRect, this, PropID);
	PropText.SetWindowTextA(std::to_string(*LinkVal).c_str());
	PropText.SetFrameRender(false);
	PropText.SetFont(CurrentFont);

	bCreated = true;

	return 0;
}

void XPropCtrlNumericU8::EditChange(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropID && LinkVal)
	{
		CString Str;
		PropText.GetWindowTextA(Str);

		std::uint8_t NewVal = (std::uint8_t)atoi(Str.operator LPCSTR());

		*LinkVal = NewVal;

		XPropCtrlBase::EditChange(uID);
	}
}

void XPropCtrlNumericU8::SetValue(std::uint8_t& RefStr)
{
	LinkVal = &RefStr;
}

void XPropCtrlNumericU8::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	PropText.SetWindowPos(nullptr, TextRect.left + 1, TextRect.top + 1, TextRect.right - 1, BaseHeight - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric ctrl
static unsigned int ID_PROPERTY_NUMERIC_S16_START = 52500;

BEGIN_MESSAGE_MAP(XPropCtrlNumericS16, XStatic)
	ON_WM_SIZE()
	ON_CONTROL_RANGE(EN_CHANGE, ID_PROPERTY_NUMERIC_S16_START, ID_PROPERTY_NUMERIC_S16_START + 500, EditChange)
END_MESSAGE_MAP()


BOOL XPropCtrlNumericS16::Create(const RECT& rect, CWnd* pParentWnd, const char* Name)
{
	XPropCtrlBase::Create(rect, pParentWnd, Name);

	CRect NameRect = rect;
	NameRect.left = NameRect.right / 2;

	PropID = ID_PROPERTY_NUMERIC_S16_START++;

	PropBack.Create("", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTER, NameRect, this, ID_PROPERTY_START++);
	PropBack.SetFont(CurrentFont);
	PropBack.SetMode(false, true);

	PropText.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_NUMBER, NameRect, this, PropID);
	PropText.SetWindowTextA(std::to_string(*LinkVal).c_str());
	PropText.SetFrameRender(false);
	PropText.SetFont(CurrentFont);

	bCreated = true;

	return 0;
}

void XPropCtrlNumericS16::EditChange(UINT uID)
{
	if (!bCreated)
		return;

	if (uID == PropID && LinkVal)
	{
		CString Str;
		PropText.GetWindowTextA(Str);

		std::int16_t NewVal = (std::int16_t)atoi(Str.operator LPCSTR());

		*LinkVal = NewVal;

		XPropCtrlBase::EditChange(uID);
	}
}

void XPropCtrlNumericS16::SetValue(std::int16_t& RefStr)
{
	LinkVal = &RefStr;
}

void XPropCtrlNumericS16::OnSize(UINT nType, int cx, int cy)
{
	XPropCtrlBase::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CRect TextRect = ClientRect;
	TextRect.left = TextRect.right / 2;
	TextRect.left -= 15;

	PropBack.SetWindowPos(nullptr, TextRect.left, TextRect.top, TextRect.right, BaseHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	PropText.SetWindowPos(nullptr, TextRect.left + 1, TextRect.top + 1, TextRect.right - 1, BaseHeight - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}