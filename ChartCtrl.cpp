#include "pch.h"
#include "ChartCtrl.h"
#include <gdiplus.h>
using namespace Gdiplus;

BEGIN_MESSAGE_MAP(XChartCtrl, CStatic)
    ON_WM_PAINT()
END_MESSAGE_MAP()

XChartCtrl::XChartCtrl()
{
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&GDIPToken, &gdiplusStartupInput, NULL);

    bNeedUpdate = false;
}

XChartCtrl::~XChartCtrl()
{
    GdiplusShutdown(GDIPToken);
}

void XChartCtrl::OnPaint()
{
    CStatic::OnPaint();

    CDC* pDC = GetDC();
    CRect Rect;
    GetClientRect(&Rect);

    int PenSize = (Rect.Width() > 800) ? 2 : 1;
    CPen leafPen(PS_SOLID, PenSize, RGB(0x40, 0x45, 0x90));
    pDC->SelectObject(&leafPen);

    CBrush leafBrush(RGB(0x14, 0x14, 0x14));
    pDC->FillRect(Rect, &leafBrush);

    if (LinesCount.x > 0)
    {
        long DeltaSizeX = Rect.Width() / LinesCount.x;
        for (long Iter = 0; Iter < LinesCount.x + 1; Iter++)
        {
            long CurXPos = DeltaSizeX * Iter;

            pDC->MoveTo(CurXPos, 0);
            pDC->LineTo(CurXPos, Rect.bottom);
        }
    }

    if (LinesCount.y > 0)
    {
        long DeltaSizeY = Rect.Height() / LinesCount.y;
        for (long Iter = 0; Iter < LinesCount.y + 1; Iter++)
        {
            long CurPosY = DeltaSizeY * Iter;

            pDC->MoveTo(0, CurPosY);
            pDC->LineTo(Rect.right, CurPosY);
        }
    }

    if (Points.empty())
        return;

    if (Type != EType::eFill)
    {
        CPen leafPen2(PS_SOLID, PenSize, RGB(0x40, 0x40, 0x9d));
        pDC->SelectObject(&leafPen2);

        pDC->MoveTo(Points[0]);

        for (CPoint Line : Points)
        {
            pDC->LineTo(Line);
        }
    }

    if (Type != EType::eLinear)
    {
        Gdiplus::Graphics* graphics = new Graphics(pDC->m_hDC);
        graphics->SetSmoothingMode(SmoothingModeAntiAlias);

        Gdiplus::GraphicsPath graphicsPath;
        SolidBrush blackBrush(Color(100, 0x40, 0x40, 0x90));

        graphics->FillPolygon(&blackBrush, (Point*)Points.data(), (int)Points.size());

        delete graphics;
    }

    ReleaseDC(pDC);
}

void XChartCtrl::SetType(EType inType)
{
    Type = inType;
}

void XChartCtrl::SetGrid(int X, int Y)
{
    LinesCount.SetPoint(X, Y);
    DataExchange();
}

bool XChartCtrl::FrameUpadte()
{
    if (bNeedUpdate)
    {
        OnPaint();
        bNeedUpdate = false;

        return true;
    }

    return false;
}

void XChartCtrl::DataExchange()
{
    bNeedUpdate = true;
}
