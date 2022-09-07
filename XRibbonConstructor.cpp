#include "pch.h"
#include "XRibbonConstructor.h"
#include "XRibbonCheckBox.h"

XRibbonConstructor::XRibbonConstructor(const CMFCRibbonInfo& info)
	: CMFCRibbonConstructor(info)
{}

XRibbonConstructor::~XRibbonConstructor()
{
	
}

CMFCRibbonBaseElement* XRibbonConstructor::CreateElement(const CMFCRibbonInfo::XElement& info) const
{
	if (info.GetElementType() == CMFCRibbonInfo::e_TypeButton_Check)
	{
		const CMFCRibbonInfo::XElementButtonCheck& infoElement = (const CMFCRibbonInfo::XElementButtonCheck&)info;

		// RadioBox
		if (strstr(info.m_strKeys, "RB"))
		{
			// Make friends list
			std::string TryStr = info.m_strKeys.operator LPCSTR();
			TryStr = TryStr.substr(2);
			int ID = atoi(TryStr.c_str());
			
			XRibbonRadioBox* pNewElement = new XRibbonRadioBox(infoElement.m_ID.m_Value, infoElement.m_strText);

			ConstructBaseElement(*pNewElement, info);
			return pNewElement;
		}

		XRibbonCheckBox* pNewElement = new XRibbonCheckBox(infoElement.m_ID.m_Value, infoElement.m_strText);

		ConstructBaseElement(*pNewElement, info);
		return pNewElement;
	}

	return CMFCRibbonConstructor::CreateElement(info);
}
