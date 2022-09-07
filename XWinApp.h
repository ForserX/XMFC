#pragma once

class XWinApp :
    public CWinAppEx
{
	DECLARE_MESSAGE_MAP()

public:
	XWinApp() noexcept;
	virtual ~XWinApp() noexcept = default;

	[[nodiscard]] HMONITOR GetMonitor() const;
	void SetMonitor(HMONITOR InMonitor);

public:
	CPoint DPI;
	float ScaleFactor;

	std::vector<std::function<void(HMONITOR)>> OnMonitorChanged;

protected:

protected:
	HMONITOR Monitor = NULL;

};

extern XWinApp* MainWnd;

float GetScaleFactorFromEnum(DEVICE_SCALE_FACTOR ScaleFactor);