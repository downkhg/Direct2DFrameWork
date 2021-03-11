#include "Colliders.h"
#include "CollisionCheck.h"
#include "ColorBrush.h"
#include "GameObject.h"
#include "SingletonRenderTarget.h"
#include "DebugHelper.h"
#include <d2d1.h>
#include <d2d1_1helper.h>

using namespace DX2DClasses;

CCircleCollider::CCircleCollider(SVector2 pos, float radius)
{
	m_vPos = pos;
	m_fRadius = radius;
}

void CCircleCollider::UpdateTransform(CTransform& trasform)
{
	D2D1_POINT_2F sPos = m_vPos.ToPoint();
	sPos = sPos * trasform.GetTransfrom();
}

void CCircleCollider::DrawOutline(CColorBrush* pColorBrush, float stroke)
{
	return CDebugHelper::DrawCircle(m_vPos, m_fRadius, pColorBrush, stroke);
}

bool CCircleCollider::ToPoint(SVector2& pos)
{
	return CCollisionCheck::OverlapPointToCircle(pos, m_vPos, m_fRadius);
}

bool CCircleCollider::ToRect(CRectCollider& rect)
{
	return CCollisionCheck::OverlapCircleToAABB(m_vPos, m_fRadius, rect.GetTopLeft(), rect.GetBottomRight());
}

bool CCircleCollider::ToBox(CBoxCollider& box)
{
	return CCollisionCheck::OverlapCircleToOBB(m_vPos, m_fRadius, box.GetTopLeft(), box.GetTopRight(), box.GetBottomRight(), box.GetTopLeft());
}

bool CCircleCollider::ToCircle(CCircleCollider& circle)
{
	return CCollisionCheck::OverlapCircleToCircle(m_vPos, m_fRadius, circle.GetPos(), circle.GetRadius());
}