#pragma once

class XEditText : public CEdit
{
    CString mHint;
    bool bFrame = true;

public:
    virtual CString GetText() const;
    void SetHint(const char* hint)
    {
        mHint = hint;
        SetWindowTextA(mHint);
    }

    void GetRect(LPRECT lpRect);
    void SetFrameRender(bool bRender);

    afx_msg int  OnCreate(LPCREATESTRUCT);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
    afx_msg void OnNcPaint();
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnSetFocus(CWnd* pNewWnd);
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

    DECLARE_MESSAGE_MAP()
};

class XEditFloat : public XEditText
{
    DECLARE_MESSAGE_MAP()

protected:
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

};

class XEditUnsigned : public XEditText
{
    DECLARE_MESSAGE_MAP()

protected:
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

};