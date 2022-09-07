#pragma once

class XCheckBox :
    public CButton
{
    DECLARE_MESSAGE_MAP()
    bool Value;

public:
    int  Create(bool bState, CWnd* ParrentWnd, long ID);
};

