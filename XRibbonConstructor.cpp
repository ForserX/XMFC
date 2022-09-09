#include "pch.h"
#include "XRibbonConstructor.h"
#include "XRibbonCheckBox.h"
#include "XRibbonPanel.h"
#include "XRibbonBar.h"

XRibbonConstructor::XRibbonConstructor(const CMFCRibbonInfo& info)
	: CMFCRibbonConstructor(info)
{
	gRibonRBManager = new XRibbonRBManager;
}

XRibbonConstructor::~XRibbonConstructor()
{
	
}

CMFCRibbonCategory* XRibbonConstructor::CreateCategory(CMFCRibbonBar& bar, const CMFCRibbonInfo::XCategory& info) const
{
	XRibbonBar* RB = static_cast<XRibbonBar*>(&bar);
	return RB->AddCategory(info.m_strName, 0, 0, GetInfo().GetImageSize(CMFCRibbonInfo::e_ImagesSmall), GetInfo().GetImageSize(CMFCRibbonInfo::e_ImagesLarge));
}

void XRibbonConstructor::ConstructRibbonBar(CMFCRibbonBar& bar) const
{
	const CMFCRibbonInfo::XRibbonBar& infoBar = GetInfo().GetRibbonBar();

	XRibbonPanel::SetNextPaneID(-10);
	bar.EnableToolTips(infoBar.m_bToolTip, infoBar.m_bToolTipDescr);
	bar.EnableKeyTips(infoBar.m_bKeyTips);
	bar.EnablePrintPreview(infoBar.m_bPrintPreview);
	CMFCRibbonFontComboBox::m_bDrawUsingFont = infoBar.m_bDrawUsingFont;

	if (infoBar.m_btnMain != NULL)
	{
		CMFCRibbonApplicationButton* btnMain = bar.GetApplicationButton();
		if (btnMain == NULL)
		{
			btnMain = CreateApplicationButton(bar);
		}

		if (btnMain != NULL)
		{
			ConstructElement(*btnMain, *infoBar.m_btnMain);
		}
	}

	if (infoBar.m_MainCategory != NULL)
	{
		ConstructCategoryMain(bar, *infoBar.m_MainCategory);
	}

	ConstructTabElements(bar, infoBar);

	for (int i = 0; i < infoBar.m_arCategories.GetSize(); i++)
	{
		const CMFCRibbonInfo::XCategory& infoCategory = *(const CMFCRibbonInfo::XCategory*)infoBar.m_arCategories[i];

		CMFCRibbonCategory* pCategory = CreateCategory(bar, infoCategory);

		XRibbonCategory* TryCategory = static_cast<XRibbonCategory*>(pCategory);

		if (TryCategory != NULL)
		{
			if (infoCategory.m_strKeys && strlen(infoCategory.m_strKeys) > 0)
			{
				TryCategory->SetGroup(infoCategory.m_strKeys.operator LPCSTR());
			}

			ASSERT_VALID(TryCategory);
			ConstructCategory(*TryCategory, infoCategory);
		}
	}

	for (int i = 0; i < infoBar.m_arContexts.GetSize(); i++)
	{
		const CMFCRibbonInfo::XContext* context = infoBar.m_arContexts[i];
		for (int j = 0; j < context->m_arCategories.GetSize(); j++)
		{
			const CMFCRibbonInfo::XCategory& infoCategory = *(const CMFCRibbonInfo::XCategory*)context->m_arCategories[j];

			CMFCRibbonCategory* pCategory = CreateCategoryContext(bar, *context, infoCategory);
			if (pCategory != NULL)
			{
				ASSERT_VALID(pCategory);
				ConstructCategory(*pCategory, infoCategory);
			}
		}
	}

	ConstructQATElements(bar, infoBar);
}

CMFCRibbonPanel* XRibbonConstructor::CreatePanel(CMFCRibbonCategory& category, const CMFCRibbonInfo::XPanel& info) const
{
	HICON hIcon = NULL;
	if (info.m_nImageIndex != -1)
	{
		hIcon = const_cast<CMFCToolBarImages&>(GetInfo().GetRibbonBar().m_Images.m_Image).ExtractIcon(info.m_nImageIndex);
	}

	return static_cast<XRibbonCategory*>(&category)->AddPanel(info.m_strName, hIcon);
}

void XRibbonConstructor::ConstructCategory(CMFCRibbonCategory& category, const CMFCRibbonInfo::XCategory& info) const
{
	const_cast<CMFCToolBarImages&>(info.m_SmallImages.m_Image).CopyTo(category.GetSmallImages());
	const_cast<CMFCToolBarImages&>(info.m_LargeImages.m_Image).CopyTo(category.GetLargeImages());

	category.SetKeys(info.m_strKeys);

	int i = 0;
	for (i = 0; i < info.m_arPanels.GetSize(); i++)
	{
		const CMFCRibbonInfo::XPanel& infoPanel = *(const CMFCRibbonInfo::XPanel*)info.m_arPanels[i];

		XRibbonPanel* pPanel = dynamic_cast<XRibbonPanel*>(CreatePanel(category, infoPanel));
		if (pPanel != NULL)
		{
			ASSERT_VALID(pPanel);
			ConstructPanel(*pPanel, infoPanel);
		}
	}

	for (i = 0; i < info.m_arElements.GetSize(); i++)
	{
		CMFCRibbonBaseElement* pElement = CreateElement(*(const CMFCRibbonInfo::XElement*)info.m_arElements[i]);

		if (pElement != NULL)
		{
			ASSERT_VALID(pElement);
			category.AddHidden(pElement);
		}
	}
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
			pNewElement->SetGroupID(ID);

			gRibonRBManager->Emplace(pNewElement);

			ConstructBaseElement(*pNewElement, info);
			return pNewElement;
		}

		XRibbonCheckBox* pNewElement = new XRibbonCheckBox(infoElement.m_ID.m_Value, infoElement.m_strText);

		ConstructBaseElement(*pNewElement, info);
		return pNewElement;
	}

	return CMFCRibbonConstructor::CreateElement(info);
}
