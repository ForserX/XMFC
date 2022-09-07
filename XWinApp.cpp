#include "pch.h"
#include "XWinApp.h"
#include <Windows.h>
#include <ShellScalingApi.h>

BEGIN_MESSAGE_MAP(XWinApp, CWinAppEx)
END_MESSAGE_MAP()

XWinApp* MainWnd = nullptr;

XWinApp::XWinApp() noexcept
{
	DPI.x = 96;
	DPI.y = 96;

	MainWnd = this;
}

HMONITOR XWinApp::GetMonitor() const
{
	return Monitor;
}

void XWinApp::SetMonitor(HMONITOR InMonitor)
{
	if (Monitor != InMonitor)
	{
		Monitor = InMonitor;

		DEVICE_SCALE_FACTOR Factor;
		HRESULT hr = GetScaleFactorForMonitor(GetMonitor(), &Factor);
		ScaleFactor = GetScaleFactorFromEnum(Factor);

		UINT InDPI[2] = {};

		hr = GetDpiForMonitor(Monitor, MDT_EFFECTIVE_DPI, &InDPI[0], &InDPI[1]);

		DPI.SetPoint((int)InDPI[0], (int)InDPI[1]);

		for (std::function<void(HMONITOR)>& Delegate : OnMonitorChanged)
		{
			Delegate(Monitor);
		}
	}
}