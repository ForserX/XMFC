#include "pch.h"
#include "XDockablePane.h"

XDockableManager* gPaneManager = new XDockableManager;

void XDockableManager::OnChangeVisualStyle()
{
	for (XDockablePane*& Pane : PaneList)
		Pane->OnChangeVisualStyle();
}

void XDockableManager::AddPane(XDockablePane* Pane)
{
	PaneList.emplace_back(Pane);
}

void XDockableManager::RemovePane(XDockablePane* Pane)
{
	auto Result = std::find(PaneList.begin(), PaneList.end(), Pane);

	if (Result != PaneList.end())
		PaneList.erase(Result);
}

//////////////////////////////////////////////////////////////////////////

XDockablePane::XDockablePane()
{
	gPaneManager->AddPane(this);
}

XDockablePane::~XDockablePane()
{
	gPaneManager->RemovePane(this);
}

void XDockablePane::OnChangeVisualStyle()
{
}