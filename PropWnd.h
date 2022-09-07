#pragma once
#include "PropCtrl.h"
#include "Button.h"

class XPropGroup : public XPropCtrl
{
	DECLARE_MESSAGE_MAP()
private:
	std::vector<XPropCtrl*> PropList;
	XStatic HeaderText;
	XStatic RightBar;
	XButton HideBtn;
	CFont CurrentFont;

	long BtnID;
	bool bVisible = true;

public:
	BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID, const char* GroupName);

public:
	XPropGroup* AddGroup(const char* GroupName);
	XPropGroup* GetGroup(const char* GroupName);

	virtual ~XPropGroup() override;

public:
	XPropCtrlText*			AddText(const char* Name, std::string& Value);
	XPropCtrlComboBox*		AddCombo(const char* Name, const std::string& List, std::string& Iterator);
	XPropCtrlNumeric*		AddNumeric(const char* Name, int& Iterator);
	XPropCtrlNumericFloat*	AddNumeric(const char* Name, float& Iterator);
	XPropCtrlNumericU32*	AddNumeric(const char* Name, unsigned int& Iterator);
	XPropCtrlNumericU16*	AddNumeric(const char* Name, std::uint16_t& Iterator);
	XPropCtrlNumericU8*		AddNumeric(const char* Name, std::uint8_t& Iterator);
	XPropCtrlNumericS16*	AddNumeric(const char* Name, std::int16_t& Iterator);
	XPropCtrlNumericS8*		AddNumeric(const char* Name, std::int8_t& Iterator);
	XPropCtrlCheck*			AddBool(const char* Name, bool& Iterator);

	void AddButton(const char* Name, const char* ButtonName, std::function<void()> Ref);
	void AddButton2(const char* Name, const char* ButtonName1 ,std::function<void()> Ref, const char* ButtonName2, std::function<void()> Ref2);
	void AddButton3(const char* Name, const char* ButtonName1 ,std::function<void()> Ref, const char* ButtonName2, std::function<void()> Ref2, const char* ButtonName3, std::function<void()> Ref3);
#if 0
	XPropCtrlNumericFV3* AddFvector(const char* Name, Fvector& Iterator);
	XPropCtrlNumericFV4* AddFvector4(const char* Name, Fvector4& Iterator);
#endif
	XPropCtrlColor*		 AddColor(const char* Name, COLORREF& Iterator);

public:
	int CalcCY() const;
	inline bool Visible() const { return bVisible;  }
	inline void SetVisible(bool Vis) { bVisible = Vis; }

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy) override;
	afx_msg void BtnHideClick(UINT uID);
};


class XPropWnd : public XStatic
{
	friend class XPropGroup;

	DECLARE_MESSAGE_MAP()
private:
	std::unordered_map<std::string, XPropGroup*> PropList;
	CRect WindowsPos;

public:
	XPropWnd();

	BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
	XPropGroup* AddGroup(const char* GroupName);
	XPropGroup* GetGroup(const char* GroupName);

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};