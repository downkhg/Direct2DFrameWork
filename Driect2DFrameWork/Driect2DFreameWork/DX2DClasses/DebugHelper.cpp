#include "DebugHelper.h"
#include "ColorBrush.h"
#include "Vector2.h"
#include "SingletonRenderTarget.h"
#include <conio.h>
#include <consoleapi.h>

using namespace DX2DClasses;

void CDebugHelper::OpenConsole()
{
	AllocConsole(); //콘솔화면 만들기
}

void CDebugHelper::CloseConsole()
{
	FreeConsole(); //콘솔화면 끄기
}

void CDebugHelper::LogConsole(const char* msg, ...)
{
	va_list arglist;
	__crt_va_start(arglist, msg);
	_vcprintf_l(msg, NULL, arglist);
	__crt_va_end(arglist);
}

void CDebugHelper::DrawCircle(SVector2& pos, float rad, CColorBrush* pColorBrush, float stroke)
{
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();
	pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), rad, rad), pColorBrush->GetColorBrush(), stroke);
}
void CDebugHelper::DrawRect(SVector2& tl, SVector2& br, CColorBrush* pColorBrush, float stroke)
{
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();
	pRenderTarget->DrawRectangle(D2D1::RectF(tl.x, tl.y, br.x, br.y), pColorBrush->GetColorBrush(), stroke);
}
void CDebugHelper::DrawPolygon(SVector2 posArr[], int size, CColorBrush* pColorBrush, float stroke)
{
	for (int i = 0; i < size; i++)
	{
		SVector2& vStart = posArr[i];
		SVector2& vEnd = posArr[i+1];
		D2D1_POINT_2F posStart = D2D1::Point2F(vStart.x, vStart.y);
		D2D1_POINT_2F posEnd = D2D1::Point2F(vEnd.x, vEnd.y);
		ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();
		pRenderTarget->DrawLine(posStart, posEnd, pColorBrush->GetColorBrush());
	}
}