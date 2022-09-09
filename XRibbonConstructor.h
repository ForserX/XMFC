#pragma once
#include <afxribbonconstructor.h>
#include "XRibbonRadioBox.h"

class XRibbonConstructor : public CMFCRibbonConstructor
{
public:
	XRibbonConstructor(const CMFCRibbonInfo& info);
	virtual ~XRibbonConstructor();

	virtual void ConstructRibbonBar(CMFCRibbonBar& bar) const override;

protected:
	virtual CMFCRibbonCategory* CreateCategory(CMFCRibbonBar& bar, const CMFCRibbonInfo::XCategory& info) const override;
	virtual CMFCRibbonPanel* CreatePanel(CMFCRibbonCategory& category, const CMFCRibbonInfo::XPanel& info) const;
	virtual void ConstructCategory(CMFCRibbonCategory& category, const CMFCRibbonInfo::XCategory& info) const override;

	[[nodiscard]] CMFCRibbonBaseElement* CreateElement(const CMFCRibbonInfo::XElement& info) const override;
};

