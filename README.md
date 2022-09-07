# XMFC
Reworked MFC Controls by Dark theme 
![image](https://user-images.githubusercontent.com/13867290/188890426-9d83b4f7-a747-4a1a-ba6c-39fb8bba3bd1.png)

# Initial API (MDI Only)
* Set parent for your base main class by `XWinApp`
* Set parent for your base main frame by `XMDIMainFrame`
* Set theme by `CVisualManagerWin10Dark`

# Chart (XChartCtrl)
![image](https://user-images.githubusercontent.com/13867290/188891110-2d2a97ca-8658-4acf-9071-1c6f108a5ffe.png)
* Call `Create` function
* Set base type (**eLinear**/**eFill**/**eMulti**) by `SetType(type)`
* Set Grid size by `SetGrid(x, y)`
* Add points to `Points` variable. 
* * Fill/Multi: you need to reduce the last point to the first

# Edit Box
* XEditText: - all user data
* XEditFloat - only float data
* XEditUnsigned - only unsigned numerics data

* `SetFrameRender(bool)` - For drawind border 
* `SetHint(string)` - to draw a hint when losing focus

![image](https://user-images.githubusercontent.com/13867290/188892695-4b0cddd9-e8ac-4f0c-b964-b48450bcc3a5.png)

# Docable Pane (XDockablePane)
* Override `OnChangeVisualStyle` if need
* Use `gPaneManager->OnChangeVisualStyle()` into theme change function 

# Other
The rest of the components are simply redrawn under the dark mode with minimal corrections.
