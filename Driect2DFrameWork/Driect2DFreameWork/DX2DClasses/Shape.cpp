#include "ColorBush.h"
#include "Shape.h"
#include "Vector2.h"

using namespace DX2DClasses;


void CRect::Set(float x, float y, float width, float height)
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_vSize.x = width;
	m_vSize.y = height;
}

void CRect::Draw(CColorBrush* pColorBrush, float stroke, bool feel)
{
	SVector2 vBR = m_vPos + m_vSize;
	                                                                                                                                           
	D2D1_POINT_2F sTL = D2D1::Point2F(m_vPos.x, m_vPos.y);
	D2D1_POINT_2F sBR = D2D1::Point2F(vBR.x, vBR.y);
	D2D1_POINT_2F sTR = D2D1::Point2F(m_vPos.x, vBR.y);
	D2D1_POINT_2F sBL = D2D1::Point2F(vBR.x, m_vPos.y);
	
	ID2D1SolidColorBrush* pColorBlush = pColorBrush->GetColorBrush();

	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();

	if (!feel)
		pRenderTarget->DrawRectangle(D2D1::RectF(sTL.x, sTL.y, sBR.x, sBR.y), pColorBlush, stroke);
	else
		pRenderTarget->FillRectangle(D2D1::RectF(sTL.x, sTL.y, sBR.x, sBR.y), pColorBlush);
}


void CCircle::Set(float x, float y, float radius)
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_fRadius = radius;
}

void CCircle::Draw(CColorBrush* pColorBrush, float stroke, bool feel)
{
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();
	if(!feel)
		pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(m_vPos.x, m_vPos.y), m_fRadius, m_fRadius), pColorBrush->GetColorBrush());
	else
		pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(m_vPos.x, m_vPos.y), m_fRadius, m_fRadius), pColorBrush->GetColorBrush());
}


void CTriangle::Set(float ax, float ay, float bx, float by, float cx, float cy)
{
	m_arrPos[0] = SVector2(ax, ay);
	m_arrPos[1] = SVector2(bx, by);
	m_arrPos[2] = SVector2(cx, cy);
}

void CTriangle::Draw(CColorBrush* pColorBrush, float stroke, bool feel)
{

	D2D1_POINT_2F sA = D2D1::Point2F(m_arrPos[0].x, m_arrPos[0].y);
	D2D1_POINT_2F sB = D2D1::Point2F(m_arrPos[1].x, m_arrPos[1].y);
	D2D1_POINT_2F sC = D2D1::Point2F(m_arrPos[2].x, m_arrPos[2].y);
	
	ID2D1SolidColorBrush* pcColorBrush = pColorBrush->GetColorBrush();
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();
	pRenderTarget->DrawLine(sA, sB, pcColorBrush, stroke);
	pRenderTarget->DrawLine(sB, sC, pcColorBrush, stroke);
	pRenderTarget->DrawLine(sC, sA, pcColorBrush, stroke);
}


void CPolygon::Set(std::list<SVector2>& listPoint)
{
	std::list<SVector2>::iterator it;
	for (it = listPoint.begin(); it != listPoint.end(); it++)
		m_listPoints.push_back(*it);
}

void CPolygon::Set(SVector2 arrPoint[], int size)
{
	for (int i = 0; i < size; i++)
	{
		m_listPoints.push_back(arrPoint[i]);
	}
}

void CPolygon::Draw(CColorBrush* pColorBrush, float stroke, bool feel)
{
	std::list<SVector2>::iterator it;
	for (it = m_listPoints.begin(); it != m_listPoints.end(); it++)
	{
		std::list<SVector2>::iterator itNext = it; itNext++;
		if (itNext == m_listPoints.end())
			itNext = m_listPoints.begin();
		SVector2 vStart = *it;
		SVector2 vEnd = *itNext;
		D2D1_POINT_2F posStart = D2D1::Point2F(vStart.x, vStart.y);
		D2D1_POINT_2F posEnd = D2D1::Point2F(vEnd.x, vEnd.y);
		ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();
		pRenderTarget->DrawLine(posStart, posEnd, pColorBrush->GetColorBrush());
	}
}