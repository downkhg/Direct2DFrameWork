#pragma once
//이미지 이동시 위치가 변경됨? 고칠때까지 사용금지. 전반적인 렌더타겟 그리기에서 문제가 발생함.
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
		void Set(SVector2& pos, SVector2& size);
		void Set(float x, float y, float width, float height);
		void Draw(CColorBrush* pColorBrush, float stroke = 1.0f, bool feel = false) override;
	};
	
	class CCircle : public CShape
	{
		SVector2 m_vPos;
		float m_fRadius;
	public:
		void Set(SVector2& center, float radius);
		void Set(float x, float y, float radius);
		void Draw(CColorBrush* pColorBrush, float stroke = 1.0f, bool feel = false) override;
	};

	class CTriangle : public CShape
	{
		SVector2 m_arrPos[3];
	public:
		void Set(SVector2& a, SVector2& b, SVector2& c);
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