#include "pch.h"
#include "EditText.h"

BEGIN_MESSAGE_MAP(XEditText, CEdit)
    ON_WM_CREATE()
    ON_WM_NCPAINT()
    ON_WM_NCCALCSIZE()
    ON_WM_SETFOCUS()
    ON_WM_KILLFOCUS()
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

int XEditText::OnCreate(LPCREATESTRUCT s)
{
	if (GetText().GetLength() == 0)
		SetHint(mHint);

	CEdit::OnCreate(s);
	return 0;
}

// calc size by text size and vertical centering
// https://stackoverflow.com/questions/25675707/inherited-cedit-control-for-vertical-centered-text-behaves-strange
void XEditText::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	CEdit::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void XEditText::OnNcPaint()
{
    CRect rectWnd;
    GetClientRect(&rectWnd);

    if (!bFrame)
        return;

    CDC* pDC = GetDC();

    CPen pen(PS_SOLID, 1, GetGlobalData()->clrWindowFrame);
    pDC->SelectObject(pen);

    pDC->MoveTo(CPoint(rectWnd.left, rectWnd.bottom));
    pDC->LineTo(CPoint(rectWnd.right, rectWnd.bottom));
    pDC->LineTo(CPoint(rectWnd.right, rectWnd.top));
    pDC->LineTo(CPoint(rectWnd.left, rectWnd.top));
    pDC->LineTo(CPoint(rectWnd.left, rectWnd.bottom));
    ReleaseDC(pDC);
}

CString XEditText::GetText() const
{
    CString text;
    this->GetWindowTextA(text);

    if (text == mHint)
        text = "";

	return text;
}

void XEditText::OnKillFocus(CWnd* pNewWnd)
{
    CString Text;
    this->GetWindowTextA(Text);

    if (Text.GetLength() == 0)
        this->SetWindowTextA(mHint);

	CEdit::OnKillFocus(pNewWnd);
}

void XEditText::OnSetFocus(CWnd* pNewWnd)
{
    CString Text;
    this->GetWindowTextA(Text);

    if (Text == mHint)
        this->SetWindowTextA("");

	CEdit::OnSetFocus(pNewWnd);
}

void XEditText::GetRect(LPRECT lpRect)
{
    CEdit::GetRect(lpRect);

	//CDC* pDC = GetDC();
	//CFont* pOldFont = pDC->SelectObject(GetFont());
    //lpRect->bottom = pDC->GetTextExtent(BannerStr).cy + MulDiv(5, GetDpiForWindow(m_hWnd), 100);
	//pDC->SelectObject(pOldFont);
	//ReleaseDC(pDC);

	const int textHeight = GetDC()->GetTextExtent(mHint).cy;
    lpRect->bottom = MulDiv(textHeight, GetDpiForWindow(m_hWnd), 100);
}

void XEditText::SetFrameRender(bool bRender)
{
    bFrame = bRender;
}

HBRUSH XEditText::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	
	bool bActive = false;

	if (nCtlColor == CTLCOLOR_EDIT || nCtlColor ==  CTLCOLOR_STATIC)
	{
		CString text;
		this->GetWindowTextA(text);
		bActive = text != mHint;

		pDC->SetTextColor(bActive ? GetGlobalData()->clrWindowText : GetGlobalData()->clrGrayedText);
	}

	return bActive ? GetGlobalData()->brWindow : *(new CBrush(GetGlobalData()->clrBarWindow));
}



BEGIN_MESSAGE_MAP(XEditFloat, XEditText)
    ON_WM_CHAR()
END_MESSAGE_MAP()

void XEditFloat::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == '.')
	{
		CString str;
		GetWindowText(str);

		if (str.Find('.') != -1)
		{
		}
		else
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	else if (nChar == '-')
	{
		CString str;
		GetWindowText(str);

		if (str.IsEmpty())
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
		else
		{
			int nSource, nDestination;
			GetSel(nSource, nDestination);

			// select all of the content at this time
			if (nSource == 0 && nDestination == str.GetLength())
			{
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
		}
	}

	// number, Backspace, Delete
	else if ((nChar >= '0' && nChar <= '9') || (nChar == 0x08) || (nChar == 0x10))
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}

BEGIN_MESSAGE_MAP(XEditUnsigned, XEditText)
    ON_WM_CHAR()
END_MESSAGE_MAP()

void XEditUnsigned::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// number, Backspace, Delete
	if ((nChar >= '0' && nChar <= '9') || (nChar == 0x08) || (nChar == 0x10))
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}
