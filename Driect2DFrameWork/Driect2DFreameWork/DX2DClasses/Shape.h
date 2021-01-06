#pragma once
#include "Vector2.h"
#include "ColorBush.h"
#include "SingletonRenderTarget.h"
#include <list>

struct ID2D1HwndRenderTarget;
struct ID2D1SolidColorBrush;

namespace DX2DClasses
{
	class CColorBrush;

	class CShape
	{
	public:
		virtual void Draw(CColorBrush* pColorBrush, float stroke, bool feel) = 0;
	};

	class CRect : public CShape
	{
		SVector2 m_vPos;
		SVector2 m_vSize;
	public:
		void Set(float x, float y, float width, float height);
		void Draw(CColorBrush* pColorBrush, float stroke = 1.0f, bool feel = false) override;
	};
	
	class CCircle : public CShape
	{
		SVector2 m_vPos;
		float m_fRadius;
	public:
		void Set(float x, float y, float radius);
		void Draw(CColorBrush* pColorBrush, float stroke = 1.0f, bool feel = false) override;
	};

	class CTriangle : public CShape
	{
		SVector2 m_arrPos[3];
	public:
		void Set(float ax, float ay, float bx, float by, float cx, float cy);
		void Draw(CColorBrush* pColorBrush, float stroke = 1.0f, bool feel = false) override;
	};

	class CPolygon : public CShape
	{
		std::list<SVector2> m_listPoints;
	public:
		void Set(std::list<SVector2>& listPoints);
		void Set(SVector2 arrPoint[], int size);
		void Draw(CColorBrush* pColorBrush, float stroke = 1.0f, bool feel = false) override;
	};
}