#pragma once

class XChartCtrl : public CStatic
{
	DECLARE_MESSAGE_MAP()

public:
	enum class EType
	{
		eLinear, 
		eFill,
		eMulti	
	};

	std::vector<CPoint> Points;
	ULONG_PTR GDIPToken;

private:
	CPoint LinesCount;
	bool bNeedUpdate;
	EType Type;

public:
	XChartCtrl();
	~XChartCtrl();

	bool FrameUpadte();
	void DataExchange();

	void SetGrid(int X, int Y);
	void SetType(EType Type);

protected:
	void OnPaint();
};

