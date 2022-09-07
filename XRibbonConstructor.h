#pragma once
#include <afxribbonconstructor.h>
#include "XRibbonRadioBox.h"

class XRibbonConstructor : public CMFCRibbonConstructor
{
public:
	XRibbonConstructor(const CMFCRibbonInfo& info);
	virtual ~XRibbonConstructor();

protected:
	[[nodiscard]] CMFCRibbonBaseElement* CreateElement(const CMFCRibbonInfo::XElement& info) const override;
};

