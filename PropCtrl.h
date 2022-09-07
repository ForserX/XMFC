#pragma once
#include "CheckBox.h"
#include "Static.h"
#include "EditText.h"
#include "ComboBox.h"
#include "Button.h"

class XPropCtrl : public XStatic
{
public:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy) = 0;
};

extern long BaseHeight;

class XPropCtrlBase : public XPropCtrl
{
	DECLARE_MESSAGE_MAP()

protected:
	XStatic PropName;
	CFont* CurrentFont;
	bool bCreated;

public:
	XPropCtrlBase();
	virtual ~XPropCtrlBase();

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual afx_msg void EditChange(UINT uID);

	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);
};

class XPropCtrlText : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XEditText PropText;
	std::string* LinkStr;
	long PropID;

public:
	virtual ~XPropCtrlText() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);
	
	void SetStr(std::string& RefStr);

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlComboBox : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	std::vector<std::string> ValList;
	XComboBox PropCombo;
	long PropComboID;

	std::string* LinkIter;

public:
	virtual ~XPropCtrlComboBox() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name, std::string List);

	void SetValue(std::string& RefIter);

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlNumeric : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XEditText PropText;
	int* LinkVal;
	long PropID;

public:
	virtual ~XPropCtrlNumeric() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(int& RefStr);

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlNumericU32 : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XEditUnsigned PropText;
	unsigned int* LinkVal;
	long PropID;

public:
	virtual ~XPropCtrlNumericU32() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(unsigned int& RefStr);

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlNumericU16 : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XEditUnsigned PropText;
	std::uint16_t* LinkVal;
	long PropID;

public:
	virtual ~XPropCtrlNumericU16() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(std::uint16_t& RefStr);
	

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlNumericU8 : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XEditUnsigned PropText;
	std::uint8_t* LinkVal;
	long PropID;

public:
	virtual ~XPropCtrlNumericU8() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(std::uint8_t& RefStr);
	

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlNumericS8 : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XEditUnsigned PropText;
	std::int8_t* LinkVal;
	long PropID;

public:
	virtual ~XPropCtrlNumericS8() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(std::int8_t& RefStr);
	

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlNumericS16 : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XEditUnsigned PropText;
	std::int16_t* LinkVal;
	long PropID;

public:
	virtual ~XPropCtrlNumericS16() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(std::int16_t& RefStr);
	

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlNumericFloat : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XEditFloat PropText;
	float* LinkVal;
	long PropID;

public:
	virtual ~XPropCtrlNumericFloat() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(float& RefStr);
	

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlCheck : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XCheckBox Box;

	bool* LinkVal;
	long PropID;

public:
	virtual ~XPropCtrlCheck() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(bool& RefStr);
	

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlButton : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XButton Button;

	std::function<void()> LinkVal;

	long PropID;

public:
	virtual ~XPropCtrlButton() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name, const char* ButtonName);

	void SetValue(std::function<void()> RefValue);

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void ButtonPush(UINT uID);
};

class XPropCtrlButton2 : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XButton Button1;
	XButton Button2;

	std::function<void()> LinkVal1;
	std::function<void()> LinkVal2;

	long PropButton1ID;
	long PropButton2ID;

public:
	virtual ~XPropCtrlButton2() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name, const char* ButtonName1, const char* Button2);

	void SetValue(std::function<void()> RefValue1, std::function<void()> RefValue2);

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void ButtonPush(UINT uID);
};

class XPropCtrlButton3 : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XButton Button1;
	XButton Button2;
	XButton Button3;

	std::function<void()> LinkVal1;
	std::function<void()> LinkVal2;
	std::function<void()> LinkVal3;

	long PropButton1ID;
	long PropButton2ID;
	long PropButton3ID;

public:
	virtual ~XPropCtrlButton3() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name, const char* ButtonName1, const char* ButtonName2, const char* ButtonName3);

	void SetValue(std::function<void()> RefValue1, std::function<void()> RefValue2, std::function<void()> RefValue3);

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void ButtonPush(UINT uID);
};
#if 0
class XPropCtrlNumericFV3 : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XEditFloat PropX;
	XEditFloat PropY;
	XEditFloat PropZ;
	Fvector* LinkVal;
	long FVID[3] = {};

public:
	virtual ~XPropCtrlNumericFV3() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(Fvector& RefStr);
	

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};

class XPropCtrlNumericFV4 : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	XStatic PropBack;
	XEditFloat PropX;
	XEditFloat PropY;
	XEditFloat PropZ;
	XEditFloat PropW;
	Fvector4* LinkVal;
	long FVID[4] = {};

public:
	virtual ~XPropCtrlNumericFV4() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(Fvector4& RefStr);
	

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void EditChange(UINT uID);
};
#endif

class XPropCtrlColor : public XPropCtrlBase
{
	DECLARE_MESSAGE_MAP()

private:
	CMFCColorButton ClrButton;
	COLORREF* LinkVal;

	long PropID;

public:
	virtual ~XPropCtrlColor() = default;
	BOOL Create(const RECT& rect, CWnd* pParentWnd, const char* Name);

	void SetValue(COLORREF& RefValue);
	

protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void ButtonPush(UINT uID);
};