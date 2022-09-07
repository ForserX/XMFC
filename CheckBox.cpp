#include "pch.h"
#include "CheckBox.h"

BEGIN_MESSAGE_MAP(XCheckBox, CButton)
END_MESSAGE_MAP()

int XCheckBox::Create(bool bState, CWnd* ParentWnd, long ID)
{
    CButton::Create("", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, { 0, 0, 10, 10 }, ParentWnd, (unsigned int)ID);

    SetCheck(bState);
    Value = bState;

    return 0;
}
