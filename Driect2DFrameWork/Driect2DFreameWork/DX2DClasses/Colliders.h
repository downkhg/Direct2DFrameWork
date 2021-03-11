#pragma once
#include "Vector2.h"

namespace DX2DClasses
{
	class CCircleCollider;
	class CRectCollider;
	class CBoxCollider;
	class CPolygon;
	class CTransform;
	class CColorBrush;

	class CCollider
	{
	public:
		virtual void UpdateTransform(CTransform& trasfrom) = 0;
		virtual void DrawOutline(CColorBrush* pColorBrush, float stroke = 1) = 0;

		virtual bool ToPoint(SVector2& vec) = 0;
		virtual bool ToRect(CRectCollider& rect) = 0;
		virtual bool ToBox(CBoxCollider& rect) = 0;
		virtual bool ToCircle(CCircleCollider& circle) = 0;
	};

	class CCircleCollider : public CCollider
	{
		SVector2 m_vPos;
		float m_fRadius;
	public:
		SVector2& GetPos() { return m_vPos; }
		float GetRadius() { return m_fRadius; }
	public:
		CCircleCollider(SVector2 pos = SVector2(), float radius = 0);
		
		void UpdateTransform(CTransform& trasform) override;
		void DrawOutline(CColorBrush* pColorBrush, float stroke = 1) override;

		bool ToPoint(SVector2& vec) override;
		bool ToRect(CRectCollider& rect) override;
		bool ToBox(CBoxCollider& box) override;
		bool ToCircle(CCircleCollider& circle) override;
		
	};

	class CRectCollider : public CCollider
	{
		SVector2 m_vTopLeft;
		SVector2 m_vBottomRigth;
	public:
		SVector2& GetTopLeft() { return m_vTopLeft; };
		SVector2& GetBottomRight() { static SVector2 tr = SVector2(m_vTopLeft.x, m_vBottomRigth.y); return m_vBottomRigth; };
		SVector2& GetTopRight() { static SVector2 tr = SVector2(m_vTopLeft.x, m_vBottomRigth.y); return tr; };
		SVector2& GetBottomLeft() { static SVector2 bl = SVector2(m_vBottomRigth.x, m_vTopLeft.y); return bl; };
	public:
		CRectCollider(SVector2 tl = SVector2(), SVector2 br = SVector2());
		
		void UpdateTransform(CTransform& trasform) override;
		void DrawOutline(CColorBrush* pColorBrush, float stroke = 1) override;

		bool ToPoint(SVector2& vec) override;
		bool ToRect(CRectCollider& rect) override;
		bool ToBox(CBoxCollider& rect) override;
		bool ToCircle(CCircleCollider& circle) override;
	};

	class CBoxCollider : public CCollider
	{
		SVector2 m_vTopLeft;
		SVector2 m_vTopRight;
		SVector2 m_vBottomRigth;
		SVector2 m_vBottomLeft;
	public:
		SVector2& GetTopLeft() { return m_vTopLeft; };
		SVector2& GetBottomRight() { return m_vBottomRigth; };
		SVector2& GetTopRight() {  return m_vTopRight; };
		SVector2& GetBottomLeft() { return m_vBottomLeft; };
	public:
		CBoxCollider(SVector2 tl = SVector2(), SVector2 br = SVector2());

		void UpdateTransform(CTransform& trasform) override;
		void DrawOutline(CColorBrush* pColorBrush, float stroke = 1) override;

		bool ToPoint(SVector2& vec) override;
		bool ToRect(CRectCollider& rect) override;
		bool ToBox(CBoxCollider& box) override;
		bool ToCircle(CCircleCollider& circle) override;
	};
}
