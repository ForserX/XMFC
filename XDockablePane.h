#pragma once

class XDockablePane : public CDockablePane
{
public:
    XDockablePane();
    virtual ~XDockablePane();

    virtual void OnChangeVisualStyle();
};

class XDockableManager
{
    std::vector<XDockablePane*> PaneList;
    
public:
    void OnChangeVisualStyle();

public:
    void AddPane(XDockablePane* Pane);
    void RemovePane(XDockablePane* Pane);
};

extern XDockableManager* gPaneManager;